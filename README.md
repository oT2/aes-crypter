# aes-crypter

## summary

aes-crypter is a small C library that aims to provide easy to use functions to encrypt and decrypt a string using AES-256-CBC algorithm.  
it only exposes 2 functions encrypt() and decrypt().

## Prerequisites

As aes-crypter uses OpenSSL's libcrypto, you will need to make it available on your system.  
On Debian:  
`sudo apt-get install libssl-dev`

## Build

Run `make`. built lib and it's header should be located here: `bin/`  

## Usage  

To add this lib to your project, copy the content of `bin` to it. Compile your project with both aes-crypter.a and libcrypto.  
example: `gcc -o my_app file1.o file2.o aes-crypter.a -lcrypto`

### Interface

```
#include "aes_crypter.h"

char  *encrypt(char *key, const char *input, int *output_len);
char  *decrypt(char *key, const char *input, int input_len);
```
where:  
- `key` is the encryption key. It should be 32 bytes long. if the provided key is too short, '0' characters will be added at the end. If it is too long, only the first 32 bytes will be used.
- `input` is the input data to be encrypted or decrypted.
- `output_len` is a pointer to an int in which the encrypted data's length will be stored.
- `input_len` is the length of the input data to decrypt.

As the encrypted data is binary data and may contain '\0' characters, encrypted data is not NULL terminated. 

### Return values

encrypt returns a pointer on a NON NULL terminated `char` array. array's length will be stored in `output_len` int. This array contains the encrypted data.   
  
decrypt returns a pointer on a NULL terminated `char` array. This array contains the non encrypted data.  

for both functions, returned (char *) should be `free(char *)` after use.
