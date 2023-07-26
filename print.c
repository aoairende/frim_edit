#include "main.h"

/**
 * print_list - Prints all elements of a linked list.
 *
 * @h: pointer to the head of the linked list.
 *
 * Return: number of nodes.
 */

size_t print_list(const list_t *h)
{
	size_t length = 0;
	const list_t *temp = NULL;
	char *num = NULL;

	/* Check if the input pointer 'h' is NULL. */
	if (!h)
		return (length);

	/* Set the temporary pointer 'temp' to the head of the list. */
	temp = h;
	while (temp)
	{
		length++;
		if (temp->str)
		{
			num = itostr(temp->len);
			/* printf("[%u] %s\n", temp->len, temp->str); */
			newputs("[");
			newputs(num);
			newputs("] ");
			_puts(temp->str);

			/* Free the memory allocated for the converted length string. */
			free(num);
		}
		else
			/* printf("[0] (nil)\n"); */
			_puts("[0] (nil)");
		temp = temp->next;
	}
	return (length);
}

/**
 * custom_print - Print formatted output to a specified file descriptor.
 *
 * @fd: file descriptor that holds the printed output.
 * @format: pointer to separator.
 * @...: arguments
 */

void custom_print(int fd, const char *const format, ...)
{
	int i = 0, va = 0;
	va_list p;
	char *s;

	va_start(p, format);

	/* Check through the characters of the format string. */
	while (format && *(format + i) != '\0')
	{
		if (format[i] == '%')
		{
			/* Check the format specifier after '%'. */
			switch (format[i + 1])
			{
				/* If format specifier is 'c', print a character. */
			case 'c':
				va = va_arg(p, int);
				write(fd, &va, 1);
				i += 2;
				break;

				/* If format specifier is 'd', print an integer. */
			case 'd':
				s = itostr(va_arg(p, int));
				write(fd, s, _strlen(s));
				i += 2;
				_free(s);
				break;

				/* If format specifier is 's', print a string. */
			case 's':
				s = va_arg(p, char *);
				write(fd, s, _strlen(s));
				i += 2;
				break;
			default:
				break;
			}
		}
		else
		{
			/* If no format specifier, write the character to the file descriptor. */
			write(fd, &format[i], 1);
			i++;
		}
	}
	va_end(p);
}
