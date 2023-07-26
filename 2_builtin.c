#include "main.h"

void execute_builtin_cmd(char **argv, int *status,
			 list_t *head_argv, FILE *stream, char ***tokens)
{
	int argv_count = 0;

	argv_count = str_count(argv);
	if (_strcmp(argv[0], "exit") == 0)
	{
		handle_exit(argv_count, argv, head_argv, stream, tokens);
	}
	else if (_strcmp(argv[0], "setenv") == 0)
	{
		process_setenv(argv_count, argv, status);
	}
	else if (_strcmp(argv[0], "unsetenv") == 0)
	{
		process_unsetenv(argv_count, argv, status);
	}
	else if (_strcmp(argv[0], "cd") == 0)
	{
		exec_cd_cmd(argv_count, argv, status);
	}
	else if (_strcmp(argv[0], "getenv") == 0)
	{
		/*printf("%s: %s\n", argv[1], _getenv(argv[1]));*/
		newputs(argv[1]);
		newputs(": ");
		_puts(_getenv(argv[1]));
	}
}

/**
 * handle_exit - execute exit builtin
 * @argv_count: number of arguments
 * @argv: pointer to strings
 * @head_argv: pointer to list
 * @stream: pointer to input stream
 * @tokens: holds address of of array of tokens
*/
void handle_exit(int argv_count, char **argv,
		 list_t *head_argv, FILE *stream, char ***tokens)
{
	int exit_code = 0;

	if (argv_count > 2)
	{
		custom_print(2, "exit\nbash: exit: %s: wrong argument count", argv[1]);
		free_all(argv, head_argv, stream, tokens, 2);
	}
	else if (argv_count == 1)
	{
		/*custom_print(2, "exit\n");*/
		free_all(argv, head_argv, stream, tokens, 0);
	}
	else
	{
		if (is_just_digits(argv[1]))
		{
			exit_code = _atoi(argv[1]);
			free_all(argv, head_argv, stream, tokens, exit_code);
		}
		else
		{
			custom_print(2, "%s: %d: %s: Illegal number: %s\n",
				     argvalues[0], argv_count, argv[0], argv[1]);
			free_all(argv, head_argv, stream, tokens, 2);
		}
	}
}

/**
 * free_all - execute exit builtin
 * @argv: pointer to strings
 * @head_argv: pointer to list
 * @stream: pointer to input stream
 * @tokens: holds address of of array of tokens
 * @exit_code: exit code
*/
void free_all(char **argv, list_t *head_argv, FILE *stream,
	      char ***tokens, int exit_code)
{
	free_resources(head_argv, argv, stream);
	free_strings(*tokens);
	free(line);
	exit(exit_code);
}
