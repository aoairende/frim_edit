#include "main.h"

char *line = NULL;

/**
 * main - Super simple shell.
 *
 * @argc: arguments count.
 * @argv: arguments values.
 *
 * Return: Always 0
 */

int main(int argc, char **argv)
{
	int status = 0;
	FILE *stream = stdin;
	size_t len = 0;
	ssize_t bytes_read = 0;
	list_t *head_main = NULL;
	char **strs_split_by_semicolon = NULL;

	argvalues = argv;
	(void)argc;
	while (1)
	{
		signal(SIGINT, handle_signal);
		if (isatty(fileno(stdin)))
			prompt_user();
		fetch_stream_line(&line, &stream, &len, &bytes_read);

		if (line == NULL || is_just_spaces(line) || *line == '#' ||
		    *line == '\n' || bytes_read == 0)
			continue;
		trunc_comment(line);
		strs_split_by_semicolon = parse_semicolon(line, head_main);

		if (!strs_split_by_semicolon || !*strs_split_by_semicolon)
		{
			handle_syntax_error(argv[0], &status);
			continue;
		}
		process_line_with_ops(&strs_split_by_semicolon, stream, &status, argv[0]);

		free_list(head_main);
		head_main = NULL;
	}

	printf("after typing exit\n");
	return (0);
}

/**
 * fetch_stream_line - Fetch a line of input from the specified stream.
 *
 * @line: pointer to a char pointer where input line is stored.
 * @stream: pointer to a FILE pointer representing the input stream.
 * @len: length of line.
 * @bytes: number of bytes read.
 */

void fetch_stream_line(char **line, FILE **stream, size_t *len, ssize_t *bytes)
{
	int exit_code = 0;
	*bytes = getline(line, len, *stream);

	/* Check if getline encounters an error. */
	if (*bytes == -1)
	{
		if (isatty(fileno(stdin)))
		{
			custom_print(2, "\n");
			exit_code = 1;
		}

		/* Free the allocated memory for the line. */
		free(*line);

		exit(exit_code);
	}
}

/**
 * handle_syntax_error - Handle errors during command interpretation.
 *
 * @s: pointer to string that caused the error.
 * @status: pointer to exit status.
 */

void handle_syntax_error(char *s, int *status)
{
	custom_print(2, ":%s Could not parse command\n", s);
	*status = 127;
}

/**
 * execute_cmds_with_ops - Handle a sequence of commands with
 * logical operators and execute.
 *
 * @ptr_to_cmd_ops: pointer to command operator data structure.
 * @stream: pointer to FILE reresenting the input stream.
 * @status: pointer to exit status.
 */

void execute_cmds_with_ops(cmd_ops *ptr_to_cmd_ops, FILE *stream, int *status)
{
	int j = 0, k = 0;

	/* Check through the command tokens array. */
	while (ptr_to_cmd_ops->cmd_tokens[j] != NULL)
	{
		/* Execute the command using handle_parsed_cmd function.*/
		handle_parsed_cmd(&(ptr_to_cmd_ops->cmd_tokens),
				  ptr_to_cmd_ops->cmd_tokens[j], stream, status);
		j++;

		/* Check if there is logical corresponding operator. */
		if (ptr_to_cmd_ops->ops_tokens[k] == NULL)
			break;

		if (*status == 0)
		{
			/* If the eit status is 0. */
			if (_strcmp(ptr_to_cmd_ops->ops_tokens[k], "&&") == 0)
			{
				k++;
				continue;
			}
			else if (_strcmp(ptr_to_cmd_ops->ops_tokens[k], "||") == 0)
			{
				k++;
				break;
			}
			else
				exit(1);
		}
		else
		{
			if (_strcmp(ptr_to_cmd_ops->ops_tokens[k], "&&") == 0)
			{
				k++;
				break;
			}
			else if (_strcmp(ptr_to_cmd_ops->ops_tokens[k], "||") == 0)
			{
				k++;
				continue;
			}
			else
				exit(1);
		}
	}
}
