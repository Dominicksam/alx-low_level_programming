#include "main.h"

/**
 * print_binary - prints the binary equivalent of a number
 * @n: number to print in binary
 */
void print_binary(unsigned long int n)
{
	int i, num = 0;
	unsigned long int numb1;

	for (i = 63; i >= 0; i--)
	{
		numb1 = n >> i;

		if (numb1 & 1)
		{
			_putchar('1');
			num++;
		}
		else if (num)
			_putchar('0');
	}
	if (!num)
		_putchar('0');
}

