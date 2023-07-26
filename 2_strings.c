#include "main.h"

/**
 * _strcat - Concatenates two strings.
 *
 * @dest: pointer to the  string to be added onto.
 * @src: pointer to the string to add on (source).
 *
 * Return: pointer to the resulting string.
 */

char *_strcat(char *dest, const char *src)
{
	/* Find the length of the destination string. */
	int len = strlen(dest);

	int i;

	for (i = 0; *(src + i) != '\0'; i++)
		dest[len + i] = src[i];

	/* Null terminate the concatenated string. */
	dest[len + i] = '\0';

	return (dest);
}

/**
 * _strcmp - compares two strings.
 *
 * @s1: pointer to first string to be compared.
 * @s2: pointer to second string to be compared.
 *
 * Return: neg value if s1 < s2, 0 if s1 = s2, pos value if s1 > s2.
 */

int _strcmp(char *s1, char *s2)
{
	int i;
	int same = 0;
	int s1_len = _strlen(s1);
	int s2_len = _strlen(s2);

	/* If the length of the strings are different, they are not equal. */
	if (s1_len != s2_len)
	{
		return (1);
	}

	/* Compare the characters of both strings until the end of 's1'. */
	for (i = 0; i < s1_len; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	/* If all characters are the same, the string is equal. */
	return (same);
}

/**
 * _strcpy - Copy string from dest to src.
 *
 * @dest: pointer to where string will be copied to.
 * @src: pointer to string to be copied.
 *
 * Return: pointer to dest.
 */

char *_strcpy(char *dest, const char *src)
{
	int len = _strlen(src);
	int i;

	for (i = 0; i < len + 1; i++)
		dest[i] = src[i];

	return (dest);
}

/**
 * _strdup - Create duplicate of string.
 *
 * @str: pointer to string to be duplicated.
 *
 * Return: pointer to the duplicated string
 */

char *_strdup(const char *str)
{
	unsigned int i;
	unsigned int len;
	char *dup_str = NULL;

	if (str == NULL)
		return (NULL);

	len = _strlen(str) + 1;

	dup_str = malloc(sizeof(char) * len);

	if (dup_str != NULL)
	{
		for (i = 0; i < len; i++)
			dup_str[i] = str[i];
	}
	return (dup_str);
}
