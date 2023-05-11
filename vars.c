#include "shell.h"
/**
 * replace_vars - replace variables in a string with their values
 * @str: the string to replace variables in
 * @status: the exit status of the last command executed
 * Return: a pointer to the replaced string, or NULL on failure
 */
char *replace_vars(char *str, int status)
{
	char *replaced = NULL, *p, *var;
	char status_str[4], pid_str[16];
	int len, var_len, pos, var_pos;

	if (!str)
	{
		return (NULL);
	}
	snprintf(pid_str, sizeof(pid_str), "%d", getpid());
	replaced = replace_str(replaced, "$$", pid_str);

	if (!replaced)
	{
		return NULL;
	}
	p = replaced;
	while ((pos = strcspn(p, "$")) != strlen(p))
	{
		len = pos;

		if (len > 0)
		{
			strncat(replaced, p, len);
		}
		var_pos = strcspn(p + pos + 1, " \t\n\r\f\v$");
		var_len = var_pos + 1;

		if (var_pos > 0)
		{
			var = malloc(var_len);
			if (!var)
			{
				free(replaced);
				return (NULL);
			}
			strncpy(var, p + pos + 1, var_pos);
			var[var_pos] = '\0';

			if (getenv(var))
			{
				strcat(replaced, getenv(var));
			}
			free(var);
		}
		else
		{
			strncat(replaced, p + pos, 1);
		}
		p += pos + var_len;
	}
	return replaced;
}

/**
 * execute_command - execute a command and return its exit status
 * @command: the command to execute
 * Return: the exit status of the command
 */
int execute_command(char *command)
{
	char *replaced = NULL, *tokens[MAX_TOKENS];
	int token_count, status;
	replaced = replace_vars(command, g_last_status);

	if (!replaced)
	{
		fprintf(stderr, "Error: failed to replace variables\n");
		return 1;
	}
	if (strcmp(tokens[0], "cd") == 0)
	{
		if (token_count > 1)
		{
			status = execute_command(tokens[1]);
		}
		else
		{
			status = execute_command(getenv("HOME"));
		}
		else if (strcmp(tokens[0], "exit") == 0)
		{
			if (token_count > 1)
			{
				status = _exiting(tokens[1]);
			}
			else
			{
				status = _exiting("0");
			}
		}
		else if (strcmp(tokens[0], "my_environ") == 0)
		{
			status = execute_my_environ();
		}
		else if (strcmp(tokens[0], "unsetenv") == 0)
		{
			if (args[1] == NULL || args[2] != NULL)
			{
				print_error("Invalid arguments");
				return (-1);
			}
			if (unset_environ(args[1]) == -1)
			{
				return (-1);
			}
			else
			{
				print_error("Command not found");
				return (-1);
			}
		}
	}
	return (0);
}
