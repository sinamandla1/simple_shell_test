#include "shell.h"
/**
 * tokenize_command - Tokenizes a given command and stores the resulting tokens
 * in a provided array.
 * @command: The command to tokenize.
 * @tokens: An array to store the resulting tokens in.
 * @token_count: A pointer to an integer to store the number of tokens.
 * Return: void
 */
void tokenize_command(const char *command, char **tokens, int *token_count)
{
	const char *delimiters = " \t\r\n\a";
	char *copy = strdup(command);
	char *token = strtok_r(copy, delimiters, &copy);

	if (copy == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}
	*token_count = 0;
	
	while (token != NULL && *token_count < MAX_TOKENS)
	{
		tokens[*token_count] = strdup(token);

		if (tokens[*token_count] == NULL)
		{
			fprintf(stderr, "Memory allocation failed\n");
			exit(1);
		}
		(*token_count)++;
		token = strtok_r(NULL, delimiters, &copy);
	}
	tokens[*token_count] = NULL;
	free(copy);
}
