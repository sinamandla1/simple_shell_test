#include "shell.h"
/**
 * remove_comment - Removes the comment part from a command
 * @command: The command string
 */
void remove_comment(char *command)
{
	char *pos = strchr(command, '#');

	if (pos != NULL)
	{
		*pos = '\0';
	}
}
