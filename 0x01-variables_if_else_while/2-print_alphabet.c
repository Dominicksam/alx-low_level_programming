#include <stdio.h>
/**
  *main - Entry point
  *Description print: alphabets in lower case and followed by a line'
  *Return: ALways 0
  */
int main(void)
{
	int n = 97;

	while (n <= 122)
	{
		putchar(n);
		n++;
	}
	putchar('\n');
	return (0);
}
