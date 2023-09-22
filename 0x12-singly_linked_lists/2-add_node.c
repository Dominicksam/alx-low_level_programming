#include <string.h>
#include <stdio.h>
#include "lists.h"
#include <stdlib.h>

/**
  *add-node - adds a node at the beginning of a lnked list
  *@head: double pointer to the list_t list
  *@str: new string to add in the mood
  *
  *Return:the address of the element or NULL ifit fails
  */

list_t *add_node(list_t **head, const char *str)
{
	list_t *new_node;
	unsigned int len = 0;

	while (str[len])
	len++;
	new_node = malloc(sizeof(list_t));

	if (new_node == NULL)
	return (NULL);

	new_node->str = strdup(str);
	new_node->len = len;
	new_node->next = (*head);
	(*head) = new_node;
	return (*head);
}
