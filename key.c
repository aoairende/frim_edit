#include "main.h"

/**
 * is_key_same - Checks if a string has same keys.
 *
 * @s: pointer to string to be checked for.
 * @substr: pointer to a key to be compared.
 *
 * Return: 1 if same, 0 otherwise.
 */

int is_key_same(char *s, const char *substr)
{
	unsigned int key_length = 0;
	unsigned int substr_length = (unsigned int)_strlen(substr);

	/* Calculate the length of the key in the string. */
	key_length = key_len(s);

	/* If length of the key in the string is not equal to the */
	/* length of the substring. */
	if (key_length != substr_length)
		return (0);

	/* Compare the characters in string and substring until */
	/* the '=' is gotten. */
	while (*s != '=')
	{
		/* If characters in string differs from corresponding */
		/* characters in unstring. */
		if (*s != *substr)
			return (0);
		s++;
		substr++;
	}
	return (1);
}

/**
 * handle_signal - Handles a signal.
 *
 * @signum: signal number received.
*/

void handle_signal(int signum)
{
	newputs("\n$ ");
	(void)signum;
}

/**
 * print_character - Writes the character c to STDOUT.
 *
 * @c: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int print_character(char c)
{
	return (write(1, &c, 1));
}

/**
 * process_dollar_sign - Interprets dollar sign occurences in the array.
 *
 * @s: pointer to string to be interpreted.
 * @status: pointer to status of executed command.
*/

void process_dollar_sign(char **s, int status)
{
	char *new_str = NULL;
	int i = 1;

	/* Checks through thr string array. */
	while (s[i] != NULL)
	{
		/* Checks if the current string starts with a '$'. */
		if (s[i][0] == '$')
		{
			if (_strlen(s[i]) == 2)
			{
				/* Replace '$$' with the PID converted to a string. */
				if (s[i][1] == '?')
				{
					new_str = itostr(status);
					free(s[i]);
					s[i] = new_str;
				}
				else if (s[i][1] == '$')
				{
					new_str = itostr(getpid());
					free(s[i]);
					s[i] = new_str;
				}
			}
			else if (_strlen(s[i]) > 2)
			{
				new_str = _getenv(++(s[i]));

				/* Replace the string with the value of the environment variable. */
				s[i] = new_str;
			}
		}
		i++;
	}
}
