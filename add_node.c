#include "main.h"

/**
 * add_node - Adds a new node at the beginning of a list_t list.
 *
 * @head: pointer to head pointer to the list.
 * @str: pointer to the string to add.
 *
 * Return: pointer to the new element.
 */

list_t *add_node(list_t **head, const char *str)
{
	/* Creates a new node and initialize it to NULL */
	list_t *temp = NULL;

	/* Checks if the input string is NULL */
	if (!str)
		return (NULL);
	temp = malloc(sizeof(list_t));
	if (!temp)
		return (NULL);

	temp->str = strdup(str);
	if (!temp->str)
	{
		free(temp);
		return (NULL);
	}

	temp->len = (unsigned int)_strlen(str);
	temp->next = NULL;

	/* Checks if the head pointer is NULL */
	if (!head)
	{
		*head = temp;
		return (temp);
	}
	temp->next = *head;
	*head = temp;

	return (temp);
}

/**
 * add_node_end - Adds a new node at the end of a list_t list.
 *
 * @head: pointer to head pointer to the list.
 * @str: pointer to the string to add.
 *
 * Return: pointer to the new element.
 */

list_t *add_node_end(list_t **head, const char *str)
{
	/* Declare a temporary node and a pointer to the list */
	list_t *temp = NULL;
	list_t *curr_node = NULL;

	if (!str)
		return (NULL);

	/* Allocates memory to the new node */
	temp = malloc(sizeof(list_t));
	if (!temp)
		return (NULL);

	temp->str = _strdup(str);
	if (!temp->str)
	{
		free(temp);
		return (NULL);
	}

	temp->len = (unsigned int)_strlen(str);
	temp->next = NULL;
	if (!*head)
	{
		*head = temp;
		return (temp);
	}

	/* Traverse the list to find the last node */
	curr_node = *head;
	while (curr_node->next)
		curr_node = curr_node->next;
	curr_node->next = temp;

	return (temp);
}
