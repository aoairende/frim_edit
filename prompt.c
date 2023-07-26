#include "main.h"

/**
 * prompt_user - prints shell prompt
*/

void prompt_user(void)
{
	newputs("$ ");
}

/**
 * newputs - prints the given string without new line.
 *
 * @s: pointer to the string to be printed.
 */

void newputs(char *s)
{
	while (*s != '\0')
	{
		print_character(*s);
		s++;
	}
}

/**
 * _puts - prints the given string.
 *
 * @s: pointer to the string to be printed.
 */

void _puts(char *s)
{
	while (*s != '\0')
	{
		print_character(*s);
		s++;
	}
	print_character('\n');
}
