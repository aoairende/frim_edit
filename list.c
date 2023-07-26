#include "main.h"

/**
 * store_str_ptrs - store the addresses of all strings in the list.
 *
 * @h: pointer to a list
 * @ptrs_to_str: pointer to strings
 *
 * Return: array of pointers to string
 */

char **store_str_ptrs(const list_t *h, char **ptrs_to_str)
{
	int i = 0;

	/* Check if the linked list is empty. */
	if (!h)
		return (NULL);

	while (h)
	{
		if (h->str)
		{
			ptrs_to_str[i] = _strdup(h->str);
			i++;
		}

		h = h->next;
	}
	ptrs_to_str[i] = NULL;

	return (ptrs_to_str);
}

/**
 * list_len - returns the number of elements in a linked list_t list.
 *
 * @h: pointer to the list.
 *
 * Return: number of elements in the list.
 */

size_t list_len(const list_t *h)
{
	size_t length = 0;
	const list_t *temp = NULL;

	if (!h)
		return (length);
	temp = h;
	while (temp)
	{
		if (temp->str)
			length++;
		temp = temp->next;
	}
	return (length);
}

/**
 * free_list - frees a list_t list.
 *
 * @head: pointer to begining of list
 */

void free_list(list_t *head)
{
	list_t *curr_node = NULL;

	if (!head)
		return;

	curr_node = head;

	while (head->next)
	{
		head = head->next;
		free(curr_node->str);
		free(curr_node);
		curr_node = head;
	}
	free(head->str);
	free(head);
}
