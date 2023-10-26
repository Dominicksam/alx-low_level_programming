#include "main.h"

/**
 * flip_bits - returns the number of bits to flip
 * @n: first number
 * @m: second number
 *
 * Return: number of bits to change
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	int i, numb_count = 0;
	unsigned long int number1;
	unsigned long int set_diff = n ^ m;

	for (i = 63; i >= 0; i--)
	{
		number1 = set_diff >> i;
		if (number1 & 1)
			numb_count++;
	}
	return (numb_count);
}
