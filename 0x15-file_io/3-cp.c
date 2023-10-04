#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

/**
 * main - Copies the content of a file to another file.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the arguments.
 *
 * Return: 0 on success, or an error code on failure.
 */
 
int main(int argc, char *argv[]) 
{
	int fd_from, fd_to, bytes_read, bytes_written;
	char buffer[BUFFER_SIZE];

	if (argc != 3)
	{
		dprintf(2, "Usage: cp file_from file_to\n");
		return 97;
	}

	fd_from = open(argv[1], O_RDONLY);

	if (fd_from == -1)
	{
		dprintf(2, "Error: Can't read from file %s\n", argv[1]);
		return 98;
	}

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(2, "Error: Can't write to file %s\n", argv[2]);
		close(fd_from);
		return 99;
	}

	while ((bytes_read = read(fd_from, buffer, BUFFER_SIZE)) > 0)
	{
		bytes_written = write(fd_to, buffer, bytes_read);
		if (bytes_written == -1)
		{
			dprintf(2, "Error: Can't write to file %s\n", argv[2]);
			close(fd_from);
			close(fd_to);
			return 99;
		}
	}
	if (bytes_read == -1)
	{
        dprintf(2, "Error: Can't read from file %s\n", argv[1]);
        close(fd_from);
        close(fd_to);
        return 98;
    }
    
    if (close(fd_from) == -1 || close(fd_to) == -1) 
    {
	dprintf(2, "Error: Can't close fd\n");
	return 100;
    }
    return 0;
}

