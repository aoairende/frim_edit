#include "main.h"

/**
 * trunc_comment - Truncates everything after the #.
 *
 * @s: string to be truncated of the comment section.
*/

void trunc_comment(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '#')
		{
			if (i != 0 && !isspace(s[i - 1]))
				return;
			s[i] = '\0';
		}
		i++;
	}
}
