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

