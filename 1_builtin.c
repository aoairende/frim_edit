#include "main.h"

/**
 * built_in - Checks if command is a built in by comparing it
 * with an array of built-in commands.
 *
 * @s: string to be checked.
 * @builtin: pointer to array of strings.
 *
 * Return: 1 if yes, 0 if no.
*/

int built_in(char *s, char **builtin)
{
	int i = 0;

	while (builtin[i] != NULL)
	{
		/* Compare the current element with the given command. */
		/* If they are equal, it means the command is a built-in command. */
		if ((_strcmp(builtin[i], s)) == 0)
		{
			return (1);
		}

		i++;
	}

	return (0);
}

/**
 * check_builtin_cm_path - Checks if there is a built in function for
 * the given command by checking if the path with command added exists.
 *
 * @arg: first argument fetched from the command line.
 * @dirs: directory paths added to first command.
 * @head: pointer to list holding.
 *
 * Return: NULL if fail, else return the full file path.
*/

char *check_builtin_cm_path(char *arg, char **dirs, list_t *head)
{
	char *path = NULL, *file_fullpath = NULL;
	int i = 0, length = 0;

	/* Checks if the argument has a forward slash at the beginning. */
	if (contains_forward_slash(arg))
	{
		/* If arguments ends with a forward slash, its an invalid path */
		if (contains_forward_slash_at_end(arg))
			return (NULL);

		/* Check if the path exists. */
		if (path_exist(arg))
			return (_strdup(arg));
		else
			return (NULL);
	}

	/* If no forward slash in argument, search the directories. */
	path = _getenv("PATH");
	dirs = str_into_tokens(path, ':', head);

	length = _strlen(arg);

	while (dirs[i] != NULL)
	{
		dirs[i] = realloc(dirs[i], _strlen(dirs[i]) + length + 2);

		/* Concatenates the directory with the argument using a forward slash. */
		_strcat(dirs[i], "/");
		_strcat(dirs[i], arg);

		if (path_exist(dirs[i]))
		{
			file_fullpath = _strdup(dirs[i]);
			break;
		}

		i++;
	}

	/* Free the linked list and temporary string array. */
	free_list(head);
	free_strings(dirs);

	return (file_fullpath);
}
