#include "main.h"

/**
 * _free - free allocated memory.
 *
 * @s: pointer to memory to free
*/

void _free(char *s)
{
	if (s != NULL)
		free(s);
	s = NULL;
}

/**
 * free_linked_list_and_strings - frees memory allocated for linked
 * lists and strings.
 *
 * @head: pointer to linked list.
 * @s: pointer to array of strings.
 */

void free_linked_list_and_strings(list_t *head, char **s)
{
	/* Free memory allocated for linked list */
	free_list(head);

	/* Free memory allocated for strs */
	free_strings(s);
}

/**
 * free_cmd_ops - free allocated memories.
 *
 * @cm_struct: structure to free
*/

void free_cmd_ops(cmd_ops *cm_struct)
{
	/* Frees the array of cmd_tokens */
	free_strings(cm_struct->cmd_tokens);

	/* Frees the array of ops_tokens */
	free_strings(cm_struct->ops_tokens);

	/* Frees the structure */
	free(cm_struct);
}

/**
 * free_resources - free memory.
 *
 * @head_argv: pointer to list to free.
 * @arg: pointer to strings to free.
 * @stream: pointer to file stream.
*/

void free_resources(list_t *head_argv, char **arg, FILE *stream)
{
	/* Frees the linked list if not NULL */
	if (head_argv != NULL)
		free_list(head_argv);

	/* Frees the array of strings if not NULL */
	if (arg != NULL)
	{
		int i = 0;

		while (arg[i] != NULL)
		{
			free(arg[i]);
			i++;
		}

		/* Frees the array of strings itself */
		free(arg[i]);
		free(arg);
	}

	/* Close the file stream if stream is not NULL */
	if (stream != NULL)
	fclose(stream);
}

/**
 * free_strings - deallocates memory.
 *
 * @s: strings to free
*/

void free_strings(char **s)
{
	int i = 0;

	/* Checks if the pointer to the strings is NULL */
	if (!s || !*s)
		return;

	/* Frees each strings until a NULL */
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}

	/* Free the strings */
	free(s);
}
