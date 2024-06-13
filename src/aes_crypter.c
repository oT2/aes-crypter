#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include "crypter_context.h"

char *encrypt(const char *input, const char *key, int *returned_len)
{
	crypter_context_t	*ctx;
	char				*return_ciphertext;
	int					len;

	if (!(ctx = new_encrypter_context(key, input)))
		return NULL;
	if (!EVP_EncryptInit_ex(ctx->evp_cipher_ctx
				, EVP_aes_256_cbc(), NULL, (unsigned char *)key, ctx->iv))
		return (char *)free_crypter_context(ctx);
	if (!EVP_EncryptUpdate(ctx->evp_cipher_ctx
				, ctx->ciphertext, &len, ctx->plaintext, ctx->plaintext_len))
		return (char *)free_crypter_context(ctx);
	ctx->ciphertext_len = len;
	if (!EVP_EncryptFinal_ex(ctx->evp_cipher_ctx, ctx->ciphertext + len, &len))
		return (char *)free_crypter_context(ctx);
	ctx->ciphertext_len += len;
	return_ciphertext = (char *)malloc(
			sizeof(char) * (ctx->ciphertext_len + sizeof(ctx->iv)));
	if (return_ciphertext == NULL)
		return (char *)free_crypter_context(ctx);
	memcpy(return_ciphertext, ctx->iv, sizeof(ctx->iv));
	memcpy(return_ciphertext + sizeof(ctx->iv) , ctx->ciphertext, ctx->ciphertext_len);
	*returned_len = ctx->ciphertext_len + sizeof(ctx->iv);
	free_crypter_context(ctx);
	return return_ciphertext;
}

char *decrypt(const char *input, const char *key, const int input_len)
{
	crypter_context_t	*ctx;
	char				*returntext;
	int					len;

	if (!(ctx = new_decrypter_context(key, input, input_len)))
		return NULL;
	if (!EVP_DecryptInit_ex(ctx->evp_cipher_ctx , EVP_aes_256_cbc()
				, NULL, ctx->key, ctx->iv))
		return NULL;
	if (!EVP_DecryptUpdate(ctx->evp_cipher_ctx, ctx->plaintext
				, &len, ctx->ciphertext, ctx->ciphertext_len))
		return NULL;
	ctx->plaintext_len = len;
	if (!EVP_DecryptFinal_ex(ctx->evp_cipher_ctx, ctx->plaintext + len, &len))
	{
		ERR_print_errors_fp(stderr);
		return NULL;
	}
	ctx->plaintext_len += len;
	returntext = (char *)malloc(sizeof(char) * ctx->plaintext_len);
	if (returntext == NULL)
		return NULL;
	memcpy(returntext, ctx->plaintext, ctx->plaintext_len);
	returntext[ctx->plaintext_len] = '\0';
	free_crypter_context(ctx);
	return returntext;
}
