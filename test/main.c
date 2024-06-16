/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~             ████████╗██████╗         
      ██████╗ ╚══██╔══╝╚════██╗        
~    ██╔═══██╗   ██║    █████╔╝        
     ██║   ██║   ██║   ██╔═══╝         
~    ╚██████╔╝   ██║   ███████╗███████╗
      ╚═════╝    ╚═╝   ╚══════╝╚══════╝
~  * File Name     : main.c
   * Creation Date : 15 Jun 2024 - 18:31:27
~  * Last Modified : 16 Jun 2024 - 14:09:36
   * Created By    : oT2_ 
~  * Email         : contact@ot2.dev 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "aes_crypter.h"

#define READ_LEN 10

char *read_all_file(int fd, int *read_size)
{
	char *buf;
	char *content;
	char *tmp;
	int  content_len;
	int  read_len;

	content_len = 0;
	content = NULL;
	if (!(buf = (char *)malloc(sizeof(char) * READ_LEN)))
		return NULL;
	while ((read_len = read(fd, buf, READ_LEN)) > 0)
	{
		if (!(tmp = malloc(sizeof(char) * (content_len + read_len))))
		{
			free(buf);
			return NULL;
		}
		if (content_len)
			memcpy(tmp, content, content_len);
		memcpy(tmp + content_len, buf, read_len);
		if (content)
			free(content);
		content = tmp;
		content_len += read_len;
	}
	free(buf);
	*read_size = content_len;
	return content;
}

int read_cmd(char *key, char *filename)
{
	int fd;
	int ciphertext_len;
	char *plaintext;
	char *ciphertext;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return 0;
	if ((ciphertext = read_all_file(fd, &ciphertext_len)) == NULL)
		return 0;
	if ((plaintext = aes_decrypt(key, ciphertext, ciphertext_len)) == NULL)
		return 0;
	printf("File content:\n%s\n", plaintext);
	free (plaintext);
	return 0;
}

int write_cmd(char *key, char *filename, char *content)
{
	char	*ciphertext;
	int		ciphertext_len;
	int		fd;

	ciphertext = aes_encrypt(key, content, &ciphertext_len);
	if (ciphertext == NULL)
		return 0;
	if ((fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) < 0)
	{
		free(ciphertext);
		return 0;
	}
	write(fd, ciphertext, ciphertext_len);
	free(ciphertext);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc > 3 && strcmp(argv[1], "read") == 0)
		return read_cmd(argv[2], argv[3]);
	else if (argc > 4 && strcmp(argv[1], "write") == 0)
		return write_cmd(argv[2], argv[3], argv[4]);
	else
		printf("usage: ./aes_test read/write KEY FILENAME [CONTENT]\n");
	return 0;
}
