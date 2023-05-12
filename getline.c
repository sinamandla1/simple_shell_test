#include "shell.h"
/**
 * get_line - reads a line from standard input
 * @length: pointer to store the length of the line
 * @position: pointer to store the current position in the buffer
 * Return: char
 */
char *get_line(int *length, int *position)
{
	char buffer[BUFFER_SIZE];
	char *line = NULL;
	int i;

	if(buffer == NULL)
	{
		return (NULL);
	}
	while (1)
	{
		if (*position >= *length)
		{
			*length = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (*length < 0)
			{
				return NULL;
			}
			else if (*length == 0)
			{
				return line;
			}
			*position = 0;
		}
		if (buffer[*position] == '\n')
		{
			buffer[*position] = '\0';
			(*position)++;
			line = malloc((*position) * sizeof(char));

			if (line == NULL)
			{
				return NULL;
			}
			for (i = 0; i < *length; i++)
			{
				line[i] = buffer[i];
			}
			return line;
		}
		(*position)++;
	}
}
