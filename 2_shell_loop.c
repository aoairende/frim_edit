#include "main.h"

/**
 * process_line_with_ops - Process and execute tokens separated by semicolon.
 *
 * @tokens: pointer to address of of array of tokens.
 * @stream: pointer to a FILE representing the input stream.
 * @status: pointer to exit status.
 * @shell_name: pointer to a string representing the shell name.
 */

void process_line_with_ops(char ***tokens, FILE *stream,
		int *status, char *shell_name)
{
	int i = 0;

	cmd_ops *ptr_to_cmd_ops = NULL;

	while ((*tokens)[i] != NULL)
	{
		if (str_contains_log_operator((*tokens)[i]))
		{
			ptr_to_cmd_ops = parse_logical_ops((*tokens)[i]);

			if (!ptr_to_cmd_ops || !ptr_to_cmd_ops->cmd_tokens ||
					!ptr_to_cmd_ops->cmd_tokens[0])
			{
				handle_syntax_error(shell_name, status);
				break;
			}
			execute_cmds_with_ops(ptr_to_cmd_ops, stream, status);
			free_cmd_ops(ptr_to_cmd_ops);
		}
		else
			handle_parsed_cmd(tokens, (*tokens)[i], stream, status);
		i++;
	}
	free_strings(*tokens);
	*tokens = NULL;
}

/**
 * handle_parsed_cmd - Handle an individual command from a
 * parsed line and execute.
 *
 * @tokens: holds address of an array of command tokens.
 * @s: pointer to string representing the individual command.
 * @stream: pointer to a FILE representing the input stream.
 * @status: pointer to exit status.
 */

void handle_parsed_cmd(char ***tokens, char *s, FILE *stream, int *status)
{
	char delim = ' ';
	char **cmds = NULL;
	list_t *head_arvg = NULL;
	char *builtin[] = {"exit", "setenv", "unsetenv", "cd", "getenv", NULL};

	/* Convert the individual command string to an array of commands. */
	cmds = str_into_tokens(s, delim, head_arvg);

	/* Check if the first token of the command matches any of the */
	/* built-in commands. */
	if (built_in(cmds[0], builtin))
	{/* Execute the built-in command. */
		execute_builtin_cmd(cmds, status, head_arvg, stream, tokens);
	}
	else
	{
		create_child_pid(status, cmds);
	}

	free_strings(cmds);
	cmds = NULL;
}
