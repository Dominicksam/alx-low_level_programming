#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/**
  *print_alphabet - Entry point
  *Description : function print_alphabet, in lowercase.
  *Return : Always (0) success
  */

void print_alphabet(void)
{
	char c = 'a';

	while (c <= 'z')
	{
		putchar(c);
		c++;
	}
	_putchar('\n');
	return (0);
}
