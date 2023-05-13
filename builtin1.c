#include "shell.h"
#include <unistd.h>
/**
 * _exiting - closes the shell
 */
void _exiting(char *status)
{
	int exit_status = 0;

	if (status != NULL)
	{
		exit_status = atoi(status);
	}
	exit(exit_status);
}

/**
 * my_environ - prints the current environment
 * @details: the environment arguments
 * Return: 0 on success or 1
 */
int my_environ(void)
{
	extern char **environ;
	char **env = environ;

	while (*env)
	{
		if (write(STDOUT_FILENO, *env, strlen(*env)) < 0)
		{
			return (1);
		}
		if (write(STDOUT_FILENO, "\n", 1) < 0)
		{
			return (1);
		}
		env++;
	}
	return (0);
}

/**
 * set_environ - Initialize a new environment variable,
 * or modify an existing one
 * @name: name of the env
 * @value: string representing the value
 * Return: 0 or otherwise
 */
int set_environ(char *name, char *value)
{
	if (!name || !value)
	{
		fprintf(stderr, "setenv: Invalid arguments\n");
		return (-1);
	}
	if (setenv(name, value, 1) != 0)
	{
		fprintf(stderr, "setenv: Failed to set environment\n");
		return (-1);
	}
	return (0);
}

/**
 * unset_environ - Remove an environment variable
 * @vari: envir variable
 * Return: 0 or -1
 */
int unset_environ(char *vari)
{
	if (!vari)
	{
		fprintf(stderr, "unsetenv: Invalid argument\n");
		return (-1);
	}
	if (unsetenv(vari) != 0)
	{
		fprintf(stderr, "unsetenv: failed to unset environment\n");
		return (-1);
	}
	return (0);
}
