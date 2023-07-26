#include "main.h"

/**
 * is_just_spaces - Checks if string has just spaces.
 *
 * @s: pointer to string to check.
 *
 * Return: 1 if string has all spaces, 0 otherwise.
 */

int is_just_spaces(char *s)
{
	int i;

	/* Loops through the characters in the string */
	for (i = 0; s[i] != '\0'; i++)
		if (!isspace(s[i]))
			return (0);
	/* If loop completes without finding a non-whitespace */
	return (1);
}

/**
 * is_just_digits - Check if a string contains just digits.
 *
 * @s: pointer to string to check.
 *
 * Return: 1 if only digits, 0 otherwise.
 */

int is_just_digits(char *s)
{
	int i = 0;

	/* Loops through the characters in the string */
	while (*(s + i) != '\0')
	{
		if (!isdigit(*(s + i)))
			return (0);
		i++;
	}

	/* If loop completes without finding a non-digit characters */
	return (1);
}

/**
 * is_semicolon_prefix - Checks if string starts with ';'
 *
 * @s: pointer to string to check.
 *
 * Return: 1 if true, 0 otherwise.
*/

int is_semicolon_prefix(char *s)
{
	int valid_char_found = 0;

	/* Loops through the characters in the string */
	while (*s != '\0')
	{
		if (*s == ';' && !valid_char_found)
			return (1);

		if (*s != ' ' && *s != '\n')
			return (0);
		s++;
	}

	/* If loop returns without finding a semicolon */
	return (0);
}

/**
 * is_semicolon_repeated - Checks if string has repeated semicolon ';'
 *
 * @s: pointer to string to check.
 *
 * Return: 1 if true, 0 otherwise
*/

int is_semicolon_repeated(char *s)
{
	int semicolon = 0;

	/* Loop through characters in the string. */
	while (*s != '\0')
	{
		if (*s == ';')
		{
			if (semicolon)
				return (1);
			semicolon = 1;
		}
		else
		{
			if (*s != ' ')
				semicolon = 0;
		}
		s++;
	}
	return (0);
}

/**
 * _atoi - Convert a string to an integer.
 *
 * @s: pointer to the string to convert.
 *
 * Return: extracted integer
 */

int _atoi(char *s)
{
	unsigned int num = 0;
	int sign = 1;
	int ch_as_int = 0;

	/* Loop through the string until a NULL terminator is encountered */
	while (*s != '\0')
	{
		/* If the character is a digit, convert to an integer */
		if (isdigit(*s))
		{
			ch_as_int = *s - '0';
			num = num * 10 + ch_as_int;
		}

		/* If a non-digit character is gotten, break the loop */
		else if (num != 0)
		{
			break;
		}

		/* If a minus sign is gotten, the sign of the number is made negative */
		if (*s == '-')
		{
			sign *= -1;
		}
		s++;
	}

	return (num * sign);
}
