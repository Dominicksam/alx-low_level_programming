#include <stdio.h>
#include <stdlib.h>

/**
  * print_listint - prints all elements of a linked list
  * @h: linked list of type listint_t to be printed
  *
  * Return : number of nodes
  */
typedef struct listint_s
{
    int n;
    struct listint_s *next;
} listint_t;

size_t print_listint(const listint_t *h)
{
	size_t node_count = 0;

		while (h != NULL)
		{
			printf("%d\n", h->n);
			h = h->next;
			node_count++;
		}
		return (node_count);
}

