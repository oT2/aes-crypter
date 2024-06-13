#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include "crypter_context.h"

crypter_context_t *encrypter_context_new(const char *key, const char *input)
{
	crypter_context_t *ctx;

	ctx = NULL;
	if (!(ctx = crypter_context_init()))
		return handle_error(ctx);
	if (!(ctx->key = sanitize_key(key)))
		return (crypter_context_t *)handle_error(ctx);
	if (!RAND_bytes(ctx->iv, sizeof(ctx->iv)))
		return handle_error(ctx);
	ctx->plaintext_len = strlen(input);
	if (!(ctx->plaintext = (unsigned char *)malloc(
					sizeof(char) * ctx->plaintext_len)))
		return handle_error(ctx);
	memcpy(ctx->plaintext, (unsigned char*)input, ctx->plaintext_len);
	ctx->ciphertext_len = ctx->plaintext_len 
		+ BLOCK_SIZE - (ctx->plaintext_len % BLOCK_SIZE);
	if (!(ctx->ciphertext = (unsigned char *)malloc(
			sizeof(char) * ctx->ciphertext_len)))
		return handle_error(ctx);
	if (!(ctx->evp_cipher_ctx = EVP_CIPHER_CTX_new()))
		return handle_error(ctx);
	return ctx;
}

crypter_context_t *decrypter_context_new(const char *key
		, const char *input, const int input_len)
{
	crypter_context_t *ctx;

	ctx = NULL;
	if (!(ctx = crypter_context_init()))
		return handle_error(ctx);
	if (!(ctx->key = sanitize_key(key)))
		return handle_error(ctx);
	ctx->ciphertext_len = input_len - sizeof(ctx->iv);
	memcpy(ctx->iv, (unsigned char *)input, sizeof(ctx->iv));
	if (!(ctx->ciphertext = (unsigned char *)malloc(
					sizeof(char) * ctx->ciphertext_len)))
		return handle_error(ctx);
	memcpy(ctx->ciphertext, (unsigned char *)input + sizeof(ctx->iv)
			, ctx->ciphertext_len);
	if (!(ctx->plaintext = (unsigned char *)malloc(ctx->ciphertext_len)))
		return handle_error(ctx);
	if (!(ctx->evp_cipher_ctx = EVP_CIPHER_CTX_new()))
		return handle_error(ctx);
	return ctx;
}

void *crypter_context_free(crypter_context_t *ctx)
{
	if (ctx->ciphertext)
		free(ctx->ciphertext);
	if (ctx->plaintext)
		free(ctx->plaintext);
	if (ctx->key)
		free(ctx->key);
	if (ctx->evp_cipher_ctx)
		EVP_CIPHER_CTX_free(ctx->evp_cipher_ctx);
	free(ctx);
	return NULL;
}

crypter_context_t *crypter_context_init()
{
	crypter_context_t *ctx;
	if (!(ctx = (crypter_context_t *)malloc(sizeof(crypter_context_t))))
		return NULL;
	ctx->evp_cipher_ctx = NULL;
	ctx->plaintext = NULL;
	ctx->ciphertext = NULL;
	ctx->key = NULL;
	return ctx;
}

unsigned char *sanitize_key(const char *key)
{
	unsigned char	*sanitized_key;
	int				key_len;

	if (!(sanitized_key = (unsigned char *)malloc(sizeof(char) * KEY_SIZE)))
		return NULL;
	key_len = strlen(key);
	memcpy(sanitized_key, key, key_len);
	while (key_len < KEY_SIZE)
	{
		sanitized_key[key_len] = '0';
		key_len++;
	}
	return sanitized_key;
}

crypter_context_t	*handle_error(crypter_context_t *ctx)
{
	// Possible future improvement: 
	// pass an int errorId as parameter. Do different things based on that id.
	// id might tell if it is a malloc error, decrypt error etc.
	// this should be turned on with an argument. as we might not want to polute stderr
	if (ctx == NULL)
		return NULL;
	if (ctx->plaintext)
		free(ctx->plaintext);
	if (ctx->ciphertext)
		free(ctx->ciphertext);
	if (ctx->key)
		free(ctx->key);
	free(ctx);
	return NULL;
}
