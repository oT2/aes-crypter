/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~             ████████╗██████╗
      ██████╗ ╚══██╔══╝╚════██╗
~    ██╔═══██╗   ██║    █████╔╝
     ██║   ██║   ██║   ██╔═══╝
~    ╚██████╔╝   ██║   ███████╗███████╗
      ╚═════╝    ╚═╝   ╚══════╝╚══════╝
~  * File Name     : aes_crypter.c
   * Creation Date : 15 Jun 2024 - 13:02:39
~  * Last Modified : 16 Jun 2024 - 14:11:26
   * Created By    : oT2_
~  * Email         : contact@ot2.dev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "crypter_context.h"

char *aes_encrypt(const char *key, const char *input, int *returned_len)
{
	crypter_context_t	*ctx;
	char				*return_ciphertext;
	int					len;

	if (!(ctx = encrypter_context_new(key, input)))
		return NULL;
	if (!EVP_EncryptInit_ex(ctx->evp_cipher_ctx
				, EVP_aes_256_cbc(), NULL, (unsigned char *)ctx->key, ctx->iv))
		return (char *)crypter_context_free(ctx);
	if (!EVP_EncryptUpdate(ctx->evp_cipher_ctx
				, ctx->ciphertext, &len, ctx->plaintext, ctx->plaintext_len))
		return (char *)crypter_context_free(ctx);
	ctx->ciphertext_len = len;
	if (!EVP_EncryptFinal_ex(ctx->evp_cipher_ctx, ctx->ciphertext + len, &len))
		return (char *)crypter_context_free(ctx);
	ctx->ciphertext_len += len;
	return_ciphertext = (char *)malloc(
			sizeof(char) * (ctx->ciphertext_len + sizeof(ctx->iv)));
	if (return_ciphertext == NULL)
		return (char *)crypter_context_free(ctx);
	memcpy(return_ciphertext, ctx->iv, sizeof(ctx->iv));
	memcpy(return_ciphertext + sizeof(ctx->iv) , ctx->ciphertext, ctx->ciphertext_len);
	*returned_len = ctx->ciphertext_len + sizeof(ctx->iv);
	crypter_context_free(ctx);
	return return_ciphertext;
}

char *aes_decrypt(const char *key, const char *input, const int input_len)
{
	crypter_context_t	*ctx;
	char				*returntext;
	int					len;

	if (!(ctx = decrypter_context_new(key, input, input_len)))
		return NULL;
	if (!EVP_DecryptInit_ex(ctx->evp_cipher_ctx , EVP_aes_256_cbc()
				, NULL, ctx->key, ctx->iv))
		return (char *)crypter_context_free(ctx);
	if (!EVP_DecryptUpdate(ctx->evp_cipher_ctx, ctx->plaintext
				, &len, ctx->ciphertext, ctx->ciphertext_len))
		return (char *)crypter_context_free(ctx);
	ctx->plaintext_len = len;
	if (!EVP_DecryptFinal_ex(ctx->evp_cipher_ctx, ctx->plaintext + len, &len))
	{
		ERR_print_errors_fp(stderr);
		return (char *)crypter_context_free(ctx);
	}
	ctx->plaintext_len += len;
	returntext = (char *)malloc(sizeof(char) * ctx->plaintext_len);
	if (returntext == NULL)
		return (char *)crypter_context_free(ctx);
	memcpy(returntext, ctx->plaintext, ctx->plaintext_len);
	returntext[ctx->plaintext_len] = '\0';
	crypter_context_free(ctx);
	return returntext;
}
