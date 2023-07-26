#include "main.h"

/**
 * create_child_pid - Creates a child process to run a command.
 *
 * @status: pointer to status of the command.
 * @arg: pointer to strings representing the command.
*/

void create_child_pid(int *status, char **arg)
{
	char **dirs = NULL;
	list_t *head_path = NULL;
	char *file_fullpath = NULL;
	pid_t child_pid;

	/* Interpret any dollar signs in the command arguments. */
	process_dollar_sign(arg, *status);

	/* Checks if the given command is built-in or an executable. */
	file_fullpath = check_builtin_cm_path(arg[0], dirs, head_path);
	if (file_fullpath == NULL)
	{
		print_nonpath_error(arg, status);
	}
	else
	{
		/* Fork a child process to execute the command. */
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			exit(2);
		}
		if (child_pid == 0)
		{
			if (execve(file_fullpath, arg, environ) == -1)
			{
				perror(arg[0]);
				*status = 2;
				exit(2);
			}
			*status = 0;
		}
		else
		{
			/* Parent pid waiting for the child process to complete executing. */
			if (wait(status) == -1)
			{
				perror("Error");
				*status = 2;
				exit(2);
			}
		}

		/* Free the memory allocated. */
		_free(file_fullpath);
		file_fullpath = NULL;
	}
}

/**
 * print_nonpath_error - Print error when a non-path command is not found.
 *
 * @status: pointer to the status of the command.
 * @arg: pointer to strings representing the command.
*/

void print_nonpath_error(char **arg, int *status)
{
	/* Check if the command doesn't have a forward slash at the beginning. */
	if (!contains_forward_slash(arg[0]))
	{
		/* Print a custom error message if command not found. */
		custom_print(2, "%s: %d: %s: not found\n", argvalues[0],
			     count_args(arg), arg[0]);
	}
	else
		/* Print error message if command has a '/' at the beginning. */
		perror(arg[0]);
	*status = 127;
}

/**
 * contains_forward_slash_at_end - Checks if a string ends with a
 * forward slash.
 *
 * @s: pointer to string to be checked for ending eith a forward slash.
 *
 * Return: 1 if string ends with forward slash, else return 0.
*/

int contains_forward_slash_at_end(char *s)
{
        if (!s)
                return (0);

        /* Checks if last character in the string is '/' */
        return (s[_strlen(s) - 1] == '/');
}

/**
 * contains_forward_slash - Checks if a string contains a forward slash.
 *
 * @s: pointer to string to be checked for a forward slash.
 *
 * Return: 1 if str contains a /, otherwise return 0.
*/

int contains_forward_slash(char *s)
{
        if (!s)
		return (0);

	/* Checks if the string contains a '/' character. */
        while (*s != '\0')
        {
                if (*s == '/')
                        return (1);
                s++;
        }
        return (0);
}
