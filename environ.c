#include "main.h"

/**
 * _getenv - Gets the value of the environment variable.
 *
 * @name: pointer to name of variable to be checked.
 *
 * Return: pointer to value of environment variable,
 * or NULL if not found.
 */

char *_getenv(const char *name)
{
	char *value = NULL;
	unsigned int i = 0;

	/* Loops through the environment variable until a NULL. */
	while (environ[i] != NULL)
	{
		if (is_key_same(environ[i], name))
			value = get_value(environ[i]);
		i++;
	}
	return (value);
}

/**
 * _setenv - Sets the value of the given environment variable
 * to value specified by user.
 *
 * @name: name of environment variable to be set.
 * @value: value to which environment variable must be set.
 * @overwrite: a flag, if set to 1 overwrite value already stored in variable.
 * otherwise if set to 0 leave variable as is and dont change.
 *
 * Return: -1 on failure, else return 0.
*/

int _setenv(const char *name, const char *value, int overwrite)
{
	int i = 0, environ_count = str_count(environ);
	char *new_env_str = NULL;
	char **new_environ = NULL;
	int new_env_var_len = strlen(name) + strlen(value) + 2;

	/* Checks if 'name' or 'value' i NULL. */
	if (!name || !value)
		return (-1);

	/*Allocate memory for the new environment variable string. */
	new_env_str = malloc(sizeof(char) * new_env_var_len);
	if (!new_env_str)
		return (-1);

	strcat(new_env_str, name);
	strcat(new_env_str, "=");
	strcat(new_env_str, value);

	/* Loops through the environment to check if 'name' exists. */
	while (environ[i])
	{
		if (strncmp(environ[i], name, strlen(name)) == 0)
		{
			if (!overwrite)
				return (0);

			/* Update existing environment varaiable with new if overwrite is allowed. */
			strncpy(environ[i], new_env_str, new_env_var_len);
			_free(new_env_str);
			new_env_str = NULL;
			return (0);
		}
		i++;
	}
	new_environ = malloc(sizeof(char *) * (environ_count + 2));
	i = 0;
	while (environ[i] != NULL)
	{
		new_environ[i] = environ[i];
		i++;
	}

	/* Checks if memory allocation for new environment s successful. */
	if (!new_environ)
		return (-1);
	environ = new_environ;
	environ[environ_count] = new_env_str;
	environ[environ_count + 1] = NULL;
	return (0);
}

/**
 * key_len - Calculate the length of environment variable's key.
 *
 * @s: pointer to environment variable string to be calculated.
 *
 * Return: length of key in the environment variaable string.
 */

unsigned int key_len(char *s)
{
	unsigned int len = 0;

	/* Loops through the characters of the string until a '='. */
	while (*s != '=')
	{
		len++;
		s++;
	}
	return (len);
}

/**
 * path_list -  Create a linked list of directories from the path
 * environment variable.
 *
 * Return: pointer to head of linked list storing path.
*/

list_t *path_list()
{
	int index = 0;
	char buffer[512];
	list_t *head = NULL;
	char *value = _getenv("PATH");

	/* Loops through the characters of the PATH environment variable. */
	while (*value != '\0')
	{
		if (*value == ':')
		{
			buffer[index] = '\0';
			
			/* create a node for the string in the buffer */
			add_node(&head, buffer);
			index = -1;
		}
		else
		{
			/* Store the character from the environment variable. */
			buffer[index] = *value;
		}
		value++;
		index++;
	}
	buffer[index] = '\0';
	
	/* create a node for the string in the buffer */
	add_node(&head, buffer);

	return (head);
}
