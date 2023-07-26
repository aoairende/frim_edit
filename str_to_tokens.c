#include "main.h"

/**
 * str_into_tokens - Creates a list that stores each token in a node
 * then creates an array of pointers to each spot in the array.
 *
 * @s: string to be tokenised.
 * @delim: delimeter used to separate the strings.
 * @head: pointe to head of list storing tokens.
 *
 * Return: NULL on failure, else return pointer to array of strings.
*/

char **str_into_tokens(const char *s, char delim, list_t *head)
{
	char buffer[1024] = {0};
	int list_length = 0;
	char **ptr_to_tokens;
	int i = 0;

	if (!s)
		return (NULL);

	while (*s != '\0')
	{
		while (*s == delim)
			s++;

		if (*s == '\0' || *s == '\n')
			break;

		while (*s != delim && *s != '\0' && *s != '\n')
		{
			buffer[i] = *s;
			s++;
			i++;
		}
		buffer[i] = '\0';
		add_node_end(&head, buffer);
		i = 0;
	}

	list_length = list_len(head);
	ptr_to_tokens = malloc(sizeof(char *) * (list_length + 1));
	ptr_to_tokens = store_str_ptrs(head, ptr_to_tokens);

	free_list(head);
	head = NULL;

	return (ptr_to_tokens);
}

/**
 * count_args - Arguments count.
 *
 * @args: pointer to array of strings.
 *
 * Return: number of arguments
*/

int count_args(char **args)
{
	int i = 0;

	if (!args || !*args)
		return (0);

	while (args[i] != NULL)
	{
		i++;
	}
	return (i);
}

/**
 * num_of_digits - Count digits in n.
 *
 * @num: number to count.
 *
 * Return: number of dogits.
 */

int num_of_digits(unsigned int num)
{
	unsigned int n = num;
	int digits = 1;

	while (n >= 10)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

/**
 * path_exist - Check if path exists.
 *
 * @s: pointer to string to check.
 *
 * Return: 0
 */

int path_exist(const char *s)
{
	struct stat st;

	return (stat(s, &st) == 0);
}
