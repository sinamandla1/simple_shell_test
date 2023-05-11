#include "shell.h"
/**
 * check_command_exists - Check if a command exists in the PATH
 * @command: Command to check
 * Return: 1 if command exists, 0 otherwise
 */
int check_command_exists(const char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");

	while (token != NULL)
	{
		char *path_entry = malloc(strlen(token) + strlen(command) + 2);
		sprintf(path_entry, "%s/%s", token, command);

		if (access(path_entry, F_OK) == 0)
		{
			free(path_entry);
			free(path_copy);
			return 1;
		}
		free(path_entry);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return 0;
}

/**
 * execute_command - Execute a command
 * @command: Command to execute
 * Return: Exit status of the command
 */
int execute_command(char *command)
{
	pid_t pid = fork();
	char cwd[1024];

	if (strcmp(command, "cd") == 0)
	{
		char *home_dir = getenv("HOME");
		if (home_dir == NULL)
		{
			fprintf(stderr, "HOME directory not found.\n");
			return (1);
		}
		if (chdir(home_dir) != 0)
		{
			perror("cd");
			return (1);
		}
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			setenv("PWD", cwd, 1);
		}
		else
		{
			perror("getcwd");
			return (1);
		}
		return (0);
	}
	if (!check_command_exists(command))
	{
		fprintf(stderr, "Command not found: %s\n", command);
		return (1);
	}
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		execlp(command, command, NULL);
		perror("execlp");
		exit(1);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
		return WEXITSTATUS(status);
	}
}
