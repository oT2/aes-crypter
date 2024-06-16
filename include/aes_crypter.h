/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~             ████████╗██████╗
      ██████╗ ╚══██╔══╝╚════██╗
~    ██╔═══██╗   ██║    █████╔╝
     ██║   ██║   ██║   ██╔═══╝
~    ╚██████╔╝   ██║   ███████╗███████╗
      ╚═════╝    ╚═╝   ╚══════╝╚══════╝
~  * File Name     : aes_crypter.h
   * Creation Date : 14 Jun 2024 - 12:18:52
~  * Last Modified : 16 Jun 2024 - 12:03:47
   * Created By    : oT2_
~  * Email         : contact@ot2.dev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef AES_CRYPTER_H
#define AES_CRYPTER_H

char *aes_encrypt(const char *key, const char *plaintext, int *returned_len);
char *aes_decrypt(const char *key, const char *ciphertext, const int ciphertext_len);

#endif
