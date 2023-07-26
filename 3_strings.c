#include "main.h"

/**
 * _strncat - Concatenates two strings.
 *
 * @dest: pointer to the  string to be added onto.
 * @src: pointer to the string to add on.
 * @n: number of src string to concatenate.
 *
 * Return: pointer to the resulting string.
 */

char *_strncat(char *dest, char *src, int n)
{
	int len = _strlen(dest);
	int i;

	for (i = 0; *(src + i) != '\0' && i < n; i++)
		dest[len + i] = src[i];
	dest[len + i] = '\0';

	return (dest);
}

/**
 * _strncpy - Copy contents of one string to another string.
 *
 * @dest: pointer to the  string to be copied to.
 * @src: pointer to the string to be copied.
 * @n: number of string src to copy.
 *
 * Return: pointer to the resulting string.
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; *(src + i) != '\0' && i < n; i++)
		dest[i] = src[i];

	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}

	return (dest);
}

/**
 * _strlen - Calculates length of a string.
 *
 * @s: pointer to string.
 *
 * Return: length of the string.
 */

int _strlen(const char *s)
{
	int len = 0;

	if (!s)
		return (0);

	while (*s != '\0')
	{
		len++;
		s++;
	}

	return (len);
}

/**
 * itostr - Converts integer to string.
 *
 * @n: integer to convert.
 *
 * Return: pointer to converted string.
 */

char *itostr(int n)
{
	int digits, digit, divisor, num, i = 0, j = 0;
	char *str = NULL;

	digits = num_of_digits(n);
	str = malloc(sizeof(char) * (digits + 1));
	num = n;

	if (!str)
		return (NULL);

	for (i = digits; i > 0; i--, j++)
	{
		divisor = calculate_power(10, i - 1);
		digit = num / divisor;

		str[j] = (digit + '0');
		num %= divisor;
	}
	str[j] = '\0';

	return (str);
}
