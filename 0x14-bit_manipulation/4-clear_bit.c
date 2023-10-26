#include "main.h"

/**
 * clear_bit - sets value of a bit to 0 at any given index
 * @n: pointer to the number 
 * @index: index of the bit to clear
 *
 * Return: 1 if it worked, -1 if an error occured
 */
int clear_bit(unsigned long int *n, unsigned int index)
{
	if (index > 63)
		return (-1);

	*n = (~(1uL << index) & *n);

	return (1);
}
