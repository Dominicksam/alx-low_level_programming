#include "main.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * read_textfile- Read text file print to the POSIX STDOUT.
 * @filename: text file to be read and print
 * @letters: number of letters to be read and print
 * Return: nw- actual number of bytes read and printed
 * 0 when function fails or filename is NULL.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	char *buff;
	ssize_t fd;
	ssize_t nw;
	ssize_t t;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);

	buff = malloc(sizeof(char) * letters);
	t = read(fd, buff, letters);
	nw = write(STDOUT_FILENO, buff, t);

	free(buff);
	close(fd);
	return (nw);
}

