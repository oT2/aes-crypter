/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~             ████████╗██████╗
      ██████╗ ╚══██╔══╝╚════██╗
~    ██╔═══██╗   ██║    █████╔╝
     ██║   ██║   ██║   ██╔═══╝
~    ╚██████╔╝   ██║   ███████╗███████╗
      ╚═════╝    ╚═╝   ╚══════╝╚══════╝
~  * File Name     : aes_crypter.c
   * Creation Date : 15 Jun 2024 - 13:02:39
~  * Last Modified : 18 Jun 2024 - 14:06:23
   * Created By    : oT2_
~  * Email         : contact@ot2.dev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "crypter_context.h"
#include "aes_crypter.h"

char *aes_encrypt_string(const char *key
		, const char *plaintext, int *ciphertext_len)
{
	int		plaintext_len;

	plaintext_len = strlen(plaintext);
	return aes_encrypt_data(key, plaintext, plaintext_len, ciphertext_len);
}

char *aes_decrypt_string(const char *key
		, const char *ciphertext, const int ciphertext_len)
{
	char		*plaintext;
	char		*plaindata;
	int			plaindata_len;

	if (!(plaindata = aes_decrypt_data(key
					, ciphertext, ciphertext_len, &plaindata_len)))
		return NULL;
	if (!(plaintext = malloc(sizeof(char) * (plaindata_len + 1))))
	{
		free(plaindata);
		return NULL;
	}
	memcpy(plaintext, plaindata, plaindata_len);
	plaintext[plaindata_len] = '\0';
	free(plaindata);
	return plaintext;
}

char *aes_encrypt_data(const char *key, const char *plaindata
		, int plaindata_len, int *cipherdata_len)
{
	crypter_context_t	*ctx;
	char				*return_cipherdata;
	int					len;

	if (!(ctx = encrypter_context_new(key, plaindata, plaindata_len)))
		return NULL;
	if (!EVP_EncryptInit_ex(ctx->evp_cipher_ctx
				, EVP_aes_256_cbc(), NULL, (unsigned char *)ctx->key, ctx->iv))
		return (char *)crypter_context_free(ctx);
	if (!EVP_EncryptUpdate(ctx->evp_cipher_ctx
				, ctx->cipherdata, &len, ctx->plaindata, ctx->plaindata_len))
		return (char *)crypter_context_free(ctx);
	ctx->cipherdata_len = len;
	if (!EVP_EncryptFinal_ex(ctx->evp_cipher_ctx, ctx->cipherdata + len, &len))
		return (char *)crypter_context_free(ctx);
	ctx->cipherdata_len += len;
	return_cipherdata = (char *)malloc(
			sizeof(char) * (ctx->cipherdata_len + sizeof(ctx->iv)));
	if (return_cipherdata == NULL)
		return (char *)crypter_context_free(ctx);
	memcpy(return_cipherdata, ctx->iv, sizeof(ctx->iv));
	memcpy(return_cipherdata + sizeof(ctx->iv)
			, ctx->cipherdata, ctx->cipherdata_len);
	*cipherdata_len = ctx->cipherdata_len + sizeof(ctx->iv);
	crypter_context_free(ctx);
	return return_cipherdata;
}

char *aes_decrypt_data(const char *key
		, const char *cipherdata, const int cipherdata_len, int *plaindata_len)
{
	crypter_context_t	*ctx;
	char				*returndata;
	int					len;

	if (!(ctx = decrypter_context_new(key, cipherdata, cipherdata_len)))
		return NULL;
	if (!EVP_DecryptInit_ex(ctx->evp_cipher_ctx , EVP_aes_256_cbc()
				, NULL, ctx->key, ctx->iv))
		return (char *)crypter_context_free(ctx);
	if (!EVP_DecryptUpdate(ctx->evp_cipher_ctx, ctx->plaindata
				, &len, ctx->cipherdata, ctx->cipherdata_len))
		return (char *)crypter_context_free(ctx);
	ctx->plaindata_len = len;
	if (!EVP_DecryptFinal_ex(ctx->evp_cipher_ctx, ctx->plaindata + len, &len))
	{
		ERR_print_errors_fp(stderr);
		return (char *)crypter_context_free(ctx);
	}
	ctx->plaindata_len += len;
	*plaindata_len = ctx->plaindata_len;
	returndata = (char *)ctx->plaindata;
	ctx->plaindata = NULL;
	crypter_context_free(ctx);
	return returndata;
}
