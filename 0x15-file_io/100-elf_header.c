#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>

void confirm_elf(unsigned char *identfy);
void print_magic(unsigned char *identfy);
void print_class(unsigned char *identfy);
void print_data(unsigned char *identfy);
void print_version(unsigned char *identfy);
void print_abi(unsigned char *identfy);
void print_osabi(unsigned char *identfy);
void print_type(unsigned int e_type, unsigned char *identfy);
void print_entry(unsigned long int e_entry, unsigned char *identfy);
void close_elf(int elf);

/**
 * confirm_elf - Comfirms if a file is an ELF file.
 * @identfy: A pointer to an array containing the ELF magic numbers.
 *
 * Description: If the file is not an ELF file - exit code 98.
 */
void confirm_elf(unsigned char *identfy)
{
	int index;

	for (index = 0; index < 4; index++)
	{
		if (identfy[index] != 127 &&
		    identfy[index] != 'E' &&
		    identfy[index] != 'L' &&
		    identfy[index] != 'F')
		{
			dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
			exit(98);
		}
	}
}

/**
 * display_magic - displays the magic numbers of an ELF header.
 * @identfy: A pointer to an array containing the ELF magic numbers.
 *
 * Description: Magic numbers are separated by spaces.
 */
void display_magic(unsigned char *identfy)
{
	int index;

	printf("  Magic:   ");

	for (index = 0; index < EI_NIDENT; index++)
	{
		printf("%02x", identfy[index]);

		if (index == EI_NIDENT - 1)
			printf("\n");
		else
			printf(" ");
	}
}

/**
 * display_class - Displays the class of an ELF header.
 * @identfy: A pointer to an array containing the ELF class.
 */
void display_class(unsigned char *identfy)
{
	printf("  Class:                             ");

	switch (identfy[EI_CLASS])
	{
	case ELFCLASSNONE:
		printf("none\n");
		break;
	case ELFCLASS32:
		printf("ELF32\n");
		break;
	case ELFCLASS64:
		printf("ELF64\n");
		break;
	default:
		printf("<unknown: %x>\n", identfy[EI_CLASS]);
	}
}

/**
 * display_data - Displays the data of an ELF header.
 * @identfy: A pointer to an array containing the ELF class.
 */
void display_data(unsigned char *identfy)
{
	printf("  Data:                              ");

	switch (identfy[EI_DATA])
	{
	case ELFDATANONE:
		printf("none\n");
		break;
	case ELFDATA2LSB:
		printf("2's complement, little endian\n");
		break;
	case ELFDATA2MSB:
		printf("2's complement, big endian\n");
		break;
	default:
		printf("<unknown: %x>\n", identfy[EI_CLASS]);
	}
}

/**
 * display_version - Prints the version of an ELF header.
 * @identfy: A pointer to an array containing the ELF version.
 */
void display_version(unsigned char *identfy)
{
	printf("  Version:                           %d",
	       identfy[EI_VERSION]);

	switch (identfy[EI_VERSION])
	{
	case EV_CURRENT:
		printf(" (current)\n");
		break;
	default:
		printf("\n");
		break;
	}
}

/**
 * display_osabi - Prints the OS/ABI of an ELF header.
 * @identfy: A pointer to an array containing the ELF version.
 */
void display_osabi(unsigned char *identfy)
{
	printf("  OS/ABI:                            ");

	switch (identfy[EI_OSABI])
	{
	case ELFOSABI_NONE:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_HPUX:
		printf("UNIX - HP-UX\n");
		break;
	case ELFOSABI_NETBSD:
		printf("UNIX - NetBSD\n");
		break;
	case ELFOSABI_LINUX:
		printf("UNIX - Linux\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("UNIX - Solaris\n");
		break;
	case ELFOSABI_IRIX:
		printf("UNIX - IRIX\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("UNIX - FreeBSD\n");
		break;
	case ELFOSABI_TRU64:
		printf("UNIX - TRU64\n");
		break;
	case ELFOSABI_ARM:
		printf("ARM\n");
		break;
	case ELFOSABI_STANDALONE:
		printf("Standalone App\n");
		break;
	default:
		printf("<unknown: %x>\n", identfy[EI_OSABI]);
	}
}

/**
 * display_abi - Displays the ABI version of an ELF header.
 * @identfy: A pointer to an array containing the ELF ABI version.
 */
void display_abi(unsigned char *identfy)
{
	printf("  ABI Version:                       %d\n",
	       identfy[EI_ABIVERSION]);
}
/**
 * display_type - displays the type of an ELF header.
 * @e_type: The ELF type.
 * @identfy: A pointer to an array containing the ELF class.
 */
void display_type(unsigned int e_type, unsigned char *identfy)
{
	if (identfy[EI_DATA] == ELFDATA2MSB)
		e_type >>= 8;

	printf("  Type:                              ");

	switch (e_type)
	{
	case ET_NONE:
		printf("NONE (None)\n");
		break;
	case ET_REL:
		printf("REL (Relocatable file)\n");
		break;
	case ET_EXEC:
		printf("EXEC (Executable file)\n");
		break;
	case ET_DYN:
		printf("DYN (Shared object file)\n");
		break;
	case ET_CORE:
		printf("CORE (Core file)\n");
		break;
	default:
		printf("<unknown: %x>\n", e_type);
	}
}

/**
 * display_entry - Diplays the entry point of an ELF header.
 * @e_entry: The address of the ELF entry point.
 * @identfy: A pointer to an array containing the ELF class.
 */
void display_entry(unsigned long int e_entry, unsigned char *identfy)
{
	printf("  Entry point address:               ");

	if (identfy[EI_DATA] == ELFDATA2MSB)
	{
		e_entry = ((e_entry << 8) & 0xFF00FF00) |
			  ((e_entry >> 8) & 0xFF00FF);
		e_entry = (e_entry << 16) | (e_entry >> 16);
	}
	if (identfy[EI_CLASS] == ELFCLASS32)
		printf("%#x\n", (unsigned int)e_entry);

	else
		printf("%#lx\n", e_entry);
}

/**
 * close_elf - Closes an ELF file.
 * @elf: The file descriptor of the ELF file.
 *
 * Description: If the file cannot be closed - exit code 98.
 */
void close_elf(int elf)
{
	if (close(elf) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", elf);
		exit(98);
	}
}

/**
 * main - Displays the information contained in the
 *        ELF header at the start of an ELF file.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: If the file is not an ELF File or
 *              the function fails - exit code 98.
 */
int main(int __attribute__((__unused__)) argc, char *argv[])
{
	Elf64_Ehdr *header;
	int o, r;

	o = open(argv[1], O_RDONLY);
	if (o == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}
	header = malloc(sizeof(Elf64_Ehdr));
	if (header == NULL)
	{
		close_elf(o);
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}
	r = read(o, header, sizeof(Elf64_Ehdr));
	if (r == -1)
	{
		free(header);
		close_elf(o);
		dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
		exit(98);
	}

	free(header);
	close_elf(o);
	return (0);
}
