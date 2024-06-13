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

char  *encrypt(char *key, char *input, int *output_len);
char  *decrypt(char *key, char *input, int input_len);
```

### Return values

encrypt returns a pointer on a NON NULL terminated `char` array. array's length will be stored in the `output_len` int. This array contains the encrypted data.   
  
decrypt returns a pointer on a NULL terminated `char` array. This array contains the non encrypted data.  

for both functions, returned (char *) should be `free(char *)` after use.
