#include "main.h"

/**
 * process_setenv - Execute the setenv command to set an environment variable.
 *
 * @argv_count: number of arguments passed to the setenv command.
 * @argv: pointer to strings containing the command and its arguments.
 * @status: pointer to status of command executed.
*/

void process_setenv(int argv_count, char **argv, int *status)
{
	/* Checks the number of arguments passed to the setenv command. */
	if (argv_count != 3)
	{
		*status = 127;
	}
	else
	{
		if ((setenv(argv[1], argv[2], 1)) == -1)
		{
			*status = 126;
		}
	}
	*status = 0;
}

/**
 * process_unsetenv - Execute the unsetenv command to remove an
 * environment variable.
 *
 * @argv_count: number of arguments passed to the unsetenv command.
 * @argv: pointer to strings containing the command and its arguments.
 * @status: pointer to status of command executed.
*/

void process_unsetenv(int argv_count, char **argv, int *status)
{
	/* Check the number of arguments passed to the unsetenv command. */
	if (argv_count != 2)
	{
		/* Print a usage error to stderr if the number of arguments is not 2. */
		newputs(argv[0]);
		newputs(":usage: ");
		_puts(argv[0]);
		*status = 127;
	}
	else
	{
		/*If the number of arguments is exactly 2, unset the environment variable. */
		if ((_unsetenv(argv[1])) == -1)
		{
			_puts("command invoked cannot execute");
			*status = 126;
		}
	}
	*status = 0;
}
