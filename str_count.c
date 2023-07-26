#include "main.h"

/**
 * str_count - Count the number of strings in an array.
 *
 * @s: pointer to array to be counted.
 *
 * Return: number of strings in array.
*/

int str_count(char **s)
{
	int i = 0;

	while (s[i] != NULL)
	{
		i++;
	}
	return (i);
}

/**
 * str_contains_log_operator - Checks if string contains a logical operator.
 *
 * @s: pointer to string to be checked.
 *
 * Return: 1 if true, else return 0.
*/

int str_contains_log_operator(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		if ((s[i] == '&' && s[i + 1] == '&') ||
		    (s[i] == '|' && s[i + 1] == '|'))
			return (1);

		i++;
	}
	return (0);
}
