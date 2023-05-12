#include "shell.h"
/**
 * _exiting - closes the shell
 * @status: details of the shel env exit
 * Return: exit status
 */
void _exiting(char *status)
{
	int exit_status = (int)strtol(status, NULL, 10);

	printf("Exiting shell..status: %d\n", exit_status);
	exit(exit_status);
}

/**
 * my_environ - prints the current environment
 * @details: the environment arguments
 * Return: 0 on success or 1
 */
int my_environ(char *details)
{
	int x = 0;

	while (details[x])
	{
		if (write(STDOUT_FILENO, &details[x], strlen(&details[x])) < 0)
		{
			return (1);
		}
		if (write(STDOUT_FILENO, "\n", 1) < 0)
		{
			return (1);
		}
		x++;
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
	int result = setenv(name, value, 1);

	if (result != 0)
	{
		fprintf(stderr, "setenv failed: %s\n", strerror(errno));
	}
	return (result);
}

/**
 * unset_environ - Remove an environment variable
 * @vari: envir variable
 * Return: 0 or -1
 */
int unset_environ(char *vari)
{
	int result = unsetenv(vari);

	if (result != 0)
	{
		fprintf(stderr, "unsetenv failed: %s\n", strerror(errno));
		return (-1);
	}
	return (result);
}

