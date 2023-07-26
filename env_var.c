#include "main.h"

/**
 * print_env - prints the keys and values of environmennt variables
 */

void print_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		_puts(environ[i]);
		i++;
	}
}

/**
 * print_dirs_in_path - prints each dir contained in the environment variable
 */

void print_dirs_in_path(void)
{
	char *value = _getenv("PATH");

	while (*value != '\0')
	{
		if (*value == ':')
		{
			print_character('\n');
		}
		else
		{
			print_character(*value);
		}
		value++;
	}
	print_character('\n');
}

/**
 * _unsetenv - Sets value of environment variable to Zero.
 *
 * @name: name of environment variable to unset.
 *
 * Return: 0 if successfully unset, otherwise return -1
*/

int _unsetenv(const char *name)
{
	int found = 0, i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], name, _strlen(name)) == 0)
		{
			_free(environ[i]);
			found = 1;
			break;
		}
		i++;
	}
	if (found)
	{
		while (environ[i])
		{
			environ[i] = environ[i + 1];
			i++;
		}
		return (0);
	}
	else
		return (-1);
}

/**
 * get_value - Get a pointer to start of an environment variable's value.
 *
 * @s: pointer to environment variable.
 *
 * Return: pointer to start of value.
 */

char *get_value(char *s)
{
	while (*s != '=')
	{
		s++;
	}
	s++;

	return (s);
}
