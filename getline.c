#include "shell.h"
/**
 * get_line - reads a line from standard input
 * Return: char
 */
char *get_line(void)
{
	char buffer[BUFFER_SIZE];
	static int length = 0, position = 0;
	char *line = NULL;
	int i;

	while (1)
	{
		if (position >= length)
		{
			length = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (length < 0)
			{
				return NULL;
			}
			else if (length == 0)
			{
				return line;
			}
		}
		if (buffer[position] == '\n')
		{
			buffer[position] = '\0';
			position++;
			line = malloc(position * sizeof(char));

			if (line == NULL)
			{
				return NULL;
			}
			for (i = 0; i < position; i++)
			{
				line[i] = buffer[i];
			}
			return line;
		}
		position++;
	}
}
