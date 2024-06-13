#ifndef AES_CRYPTER_H
#define AES_CRYPTER_H

char *encrypt(const char *plaintext, const char *key, int *returned_len);
char *decrypt(const char *ciphertext, const char *key, const int ciphertext_len);

#endif
