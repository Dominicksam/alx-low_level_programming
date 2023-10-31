#include "main.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * read_textfile- read text file print to the POSIX STDOUT.
 * @filename: text file to be read and print
 * @letters: number of letters to be read and print
 * Return: num_bt- actual number of bytes read and printed
 * 0 when function fails or filename is NULL.
 */
size_t read_textfile(const char *filename, size_t letters)
{
	char *buff;
	ssize_t file_d;
	ssize_t num_bt;
	ssize_t t;

	file_d = open(filename, O_RDONLY);
	if (file_d == -1)
		return (0);

	buff = malloc(sizeof(char) * letters);
	t = read(file_d, buff, letters);
	num_bt = write(STDOUT_FILENO, buff, t);

	free(buff);
	close(file_d);
	return (num_bt);
}
