/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~             ████████╗██████╗
      ██████╗ ╚══██╔══╝╚════██╗
~    ██╔═══██╗   ██║    █████╔╝
     ██║   ██║   ██║   ██╔═══╝
~    ╚██████╔╝   ██║   ███████╗███████╗
      ╚═════╝    ╚═╝   ╚══════╝╚══════╝
~  * File Name     : aes_crypter.h
   * Creation Date : 14 Jun 2024 - 12:18:52
~  * Last Modified : 18 Jun 2024 - 14:41:10
   * Created By    : oT2_
~  * Email         : contact@ot2.dev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef AES_CRYPTER_H
#define AES_CRYPTER_H

char *aes_encrypt_string(const char *key
		, const char *plaintext, int *cipherdata_len);
char *aes_decrypt_string(const char *key
		, const char *cipherdata, const int cipherdata_len);
char *aes_encrypt_data(const char *key
		, const char *plaindata, int plaindata_len, int *cipherdata_len);
char *aes_decrypt_data(const char *key
		, const char *cipherdata, const int cipherdata_len, int *plaindata_len);

#endif
