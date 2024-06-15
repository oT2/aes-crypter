/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~             ████████╗██████╗
      ██████╗ ╚══██╔══╝╚════██╗
~    ██╔═══██╗   ██║    █████╔╝
     ██║   ██║   ██║   ██╔═══╝
~    ╚██████╔╝   ██║   ███████╗███████╗
      ╚═════╝    ╚═╝   ╚══════╝╚══════╝
~  * File Name     : aes_crypter.h
   * Creation Date :
~  * Last Modified : 15 Jun 2024 - 12:18:52
   * Created By    : oT2_
~  * Email         : contact@ot2.dev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef AES_CRYPTER_H
#define AES_CRYPTER_H

char *encrypt(const char *plaintext, const char *key, int *returned_len);
char *decrypt(const char *ciphertext, const char *key, const int ciphertext_len);

#endif
