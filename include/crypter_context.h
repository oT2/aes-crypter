#ifndef ENCRYPTCONTEXT_H
#define ENCRYPTCONTEXT_H

#include <openssl/evp.h>

#define BLOCK_SIZE 16
#define IV_SIZE 16
#define KEY_SIZE 32

typedef struct crypter_context
{
	EVP_CIPHER_CTX	*evp_cipher_ctx;
	unsigned char	*plaintext;
	unsigned char	*ciphertext;
	unsigned char	*key;
	unsigned char	iv[IV_SIZE];
	int				plaintext_len;
	int				ciphertext_len;

} crypter_context_t;

crypter_context_t	*encrypter_context_new(const char *key, const char *input);
crypter_context_t	*decrypter_context_new(const char *key
		, const char *input, const int input_len);
void				*crypter_context_free(crypter_context_t *crypter_ctx);
crypter_context_t	*crypter_context_init();
unsigned char		*sanitize_key(const char *key);
crypter_context_t	*handle_error(crypter_context_t *ctx);

#endif
