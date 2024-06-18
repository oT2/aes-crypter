# aes-crypter

## summary

aes-crypter is a small C library that aims to provide easy to use functions to encrypt and decrypt data.  
Encryption is done using the AES-256-CBC algorithm.

## Prerequisites

As aes-crypter encapsulates OpenSSL's libcrypto, you will need to install it on your system.  
On Debian:  
`sudo apt-get install libssl-dev`

## Build

Run `make`. Built lib and it's header should be located in: `bin/`  
  
Run `make aes_test` to build the test program, this small program encrypts a string into a file, or decrypt a file and prints it's output.  
usage: `./aes_test read/write KEY FILENAME [CONTENT]`

## Usage  

To use this lib, copy the content of `bin` to your project. Compile your project with both libaes-crypter.a and libcrypto.  
example: `gcc -o my_app file1.o file2.o -LPATH_TO_LIB -laes_crypter -lcrypto`

### Interface

```
#include "aes_crypter.h"

char *aes_encrypt_string(const char *key, const char *plaintext, int *cipherdata_len);
char *aes_decrypt_string(const char *key, const char *cipherdata, const int cipherdata_len);

char *aes_encrypt_data(const char *key, const char *plaindata, int plaindata_len, int *cipherdata_len);
char *aes_decrypt_data(const char *key, const char *cipherdata, const int cipherdata_len, int *plaindata_len);
```
where:  
- `key` is the encryption key. It should be 32 bytes long. if the provided key is too short, '0' characters will be appended to it. If it is too long, only the first 32 bytes will be used.
- `plaintext` is the NULL terminated string to be encrypted.  
- `plaindata` is the NON NULL terminated char array to be encrypted.
- `plaindata_len` is the plaindata array's length.
- `cipherdata` is the encrypted char array.
- `cipherdata_len` is the cipherdata array's length.

As the encrypted data is binary data and may contain '\0' characters, encrypted data is not NULL terminated. 

### Return values

`aes_encrypt_string()` and `aes_encrypt_data()` returns a pointer on a NON NULL terminated char array. array's length will be stored in the `cipherdata_len` int.  
  
`aes_decrypt_string()` returns a pointer on a NULL terminated char array.  
`aes_decrypt_data()` returns a pointer on a NON NULL terminated char array. Array's length will be stored in the `plaindata_len` int.

for all functions, returned (char *) should be `free()` after use.  

note: IV is prepended to the encrypted data. 
