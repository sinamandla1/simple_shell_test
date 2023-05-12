#include "shell.h"
/**
 * main - entry point of shell
 * Return: 0
 */
int main(int argc, char **argv)
{
	char command[100];
	char *tokens[MAX_TOKENS];
	int token_count, i, status;
	FILE *fp = NULL;
	
	if (argc > 1)
	{
		fp = fopen(argv[1], "r");

		if (fp == NULL)
		{
			perror("Failed to open file");
			exit(EXIT_FAILURE);
		}
	}
	while (1)
	{
		if (fp == NULL)
		{
			printf("$ ");
			fflush(stdout);
			fgets(command, sizeof(command), stdin);
			command[strcspn(command, "\n")] = '\0';
			remove_comment(command);
		}
		else
		{
			if (fgets(command, sizeof(command), fp) == NULL)
			{
				break;
			}
			command[strcspn(command, "\n")] = '\n';
			printf("$ %s\n", command);
		}
		if (command[0] == '\0')
		{
			continue;
		}
		if (strcmp(command, "exit") == 0)
		{
			_exiting("0");
		}
		else if (strcmp(command, "my_environ") == 0)
		{
			my_environ(command);
		}
		else if (strcmp(command, "set_environ") == 0)
		{
			set_environ(command, command);
		}
		else if (strcmp(command, "unset_environ") == 0)
		{
			unset_environ(command);
		}
		else
		{
			tokenize_command(command, tokens, &token_count);
			if (tokens[0] == NULL)
			{
				continue;
			}
			if (strcmp(tokens[0], "exit") == 0)
			{
				if (token_count > 1)
				{
					_exiting(tokens[1]);
				}
				else
				{
					_exiting("0");
				}
			}
			else
			{
				status = execute_command(command);
				for (i = 0; i < token_count; i++)
				{
					free(tokens[i]);
					tokens[i] = NULL;
				}
				printf("Command exited with status: %d\n", status);
			}
		}
	}
	if (fp != NULL)
	{
		fclose(fp);
	}
	return (0);
}
