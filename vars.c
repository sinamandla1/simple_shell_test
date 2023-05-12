#include "shell.h"
/**
 * replace_vars - replace variables in a string with their values
 * @str: the string to replace variables in
 * @status: the exit status of the last command executed
 * Return: a pointer to the replaced string, or NULL on failure
 */
char *replace_vars(char *str)
{
	char *replaced = NULL, *p, *var;
	char pid_str[16];
	int len, var_len, pos, var_pos;

	if (!str)
	{
		return (NULL);
	}
	snprintf(pid_str, sizeof(pid_str), "%d", getpid());
	replaced = strdup(str);

	if (!replaced)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return (NULL);
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
				fprintf(stderr, "Memory allocation failed\n");
				return (NULL);
			}
			strncpy(var, p + pos + 1, var_pos);
			var[var_pos] = '\0';

			if (strcmp(var, "$$") == 0)
			{
				strcat(replaced, pid_str);
			}
			else if (strcmp(var, "?") == 0)
			{
				char status_str[16];
				snprintf(status_str, sizeof(status_str), "%d", status);
				strcat(replaced, status_str);
			}
			else if (getenv(var))
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
 * execute_vars - execute a command and return its exit status
 * @command: the command to execute
 * Return: the exit status of the command
 */
int execute_vars(char *command)
{
	char *replaced = NULL, *tokens[MAX_TOKENS];
	int token_count, status;
	replaced = replace_vars(command, 0);

	if (!replaced)
	{
		fprintf(stderr, "Error: failed to replace variables\n");
		return (1);
	}
	tokenize_command(replaced, tokens, &token_count);

	free(replaced);
	if (strcmp(tokens[0], "cd") == 0)
	{
		if (token_count > 1)
		{
			status = execute_command(tokens[1]);
		}
		else
		{
			char *home_dir = getenv("HOME");
			if (!home_dir)
			{
				fprintf(stderr, "HOME directory not found.\n");
				return (1);
			}
			status = execute_command(home_dir);
		}
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
		status = my_environ();
	}
	else if (strcmp(tokens[0], "unsetenv") == 0)
	{
		if (tokens < 2 || tokens > 2)
		{
			fprintf(stderr, "Invalid arguments\n");
		}
		else if (unset_environ(tokens[1]) == -1)
		{
			fprintf(stderr, "Error unsetting environment variable\n");
		}
		else
		{
			fprintf(stderr, "Command not found\n");
		}
		status = -1;
	}
	else
	{
		status = execute_command(tokens[0]);
	}
	return (status);
}
