#include "main.h"

/**
 * exec_cd_cmd - Execute the cd command to change directory.
 *
 * @argv_count: number of arguments passed to the cd command.
 * @argv: pointer to strings containing the command and its arguments.
 * @status: pointer to integer representing the status of the code.
*/

void exec_cd_cmd(int argv_count, char **argv, int *status)
{
	char *env_value = NULL, *curr_dir = NULL, *home_value = NULL;

	/* Duplicate the value of th PWD environment variable to the current */
	/* directory variable. */
	curr_dir = _strdup(_getenv("PWD"));

	/* Duplicate the value of the OLDPWD environment variable to the */
	/* environment end variable. */
	env_value = _strdup(_getenv("OLDPWD"));

	/* Check the number of arguments passed to the cd command. */
	if (argv_count > 2)
		handle_usage_err(argv[0], status);
	else if (argv_count == 2)
	{
		if (_strcmp(argv[1], "-") == 0)
		{
			if (chdir(env_value) == -1)
				handle_err(argv[0], argv[1], status);
			else
				set_old_new_pwd(curr_dir, env_value, status);
		}
		else
		{
			if (chdir(argv[1]) == -1)
				handle_err(argv[0], argv[1], status);
			else
			{

				set_old_new_pwd(curr_dir, argv[1], status);
			}
		}
	}
	else
	{
		home_value = _strdup(_getenv("HOME"));
		if (chdir(home_value) == -1)
			handle_err(argv[0], argv[1], status);
		else
			set_old_new_pwd(curr_dir, home_value, status);
	}

	/* Frees the memory allocated. */
	free(curr_dir);
	free(env_value);
	free(home_value);
}

/**
 * handle_err - Handle and print an error condition.
 *
 * @str_1: pointer to first string.
 * @str_2: pointer to second string.
 * @status: pointer to an int representing the status of the executed command.
*/

void handle_err(char *str_1, char *str_2, int *status)
{
	(void)str_1;
	(void)str_2;

	*status = 0;
}

/**
 * set_old_new_pwd - Sets the values of the OLDPWD and PWD in env variables.
 *
 * @old_dir: pointer to string to set for OLDPWD.
 * @new_dir: pointer to string to set for PWD.
 * @status: pointer to an integer representing the status of the executed code.
*/

void set_old_new_pwd(char *old_dir, char *new_dir, int *status)
{
	setenv("OLDPWD", old_dir, 1);
	setenv("PWD", new_dir, 1);
	*status = 0;
}

/**
 * handle_usage_err - Handles a usage error for a command.
 *
 * @str: pointer to string usage error.
 * @status: pointer to status of the executed command.
*/

void handle_usage_err(char *str, int *status)
{
	(void)str;

	*status = 0;
}
