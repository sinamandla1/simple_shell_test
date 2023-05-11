#include "shell.h"
/**
 * interact_mode - tests if shell is in inactive mode
 * @detail: ptr to structure address
 * Return: 1 if enabled or 0
 */
int interact_mode(int stdin_fd)
{
	if (stdin_fd == -1)
	{
		return (0);
	}
	if (isatty(STDIN_FILENO))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * isDelimiter - checks if a character is a delim
 * @str: a string to be checked
 * Return: 1 if true or 0
 */
int isDelimiter(char *str)
{
	char *delimit = ",;:. \t";

	while (*str != '\0')
	{
		if (strchr(delimit, *str) != NULL)
		{
			return (1);
		}
		str++;
	}
	return (0);
}

/**
 * is_alpha - checks if a character is an alpha
 * @c: character to be checked
 * Return: 1 if true or 0
 */
int is_alpha(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (1);
	}
	if (c >= 'a' && c <= 'z')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * string_to_int - converts any string into an int
 * @str: a string to be checked and converted
 * @res: result of process
 * Return: 0 or 1 if an error occurs
 */
int string_to_int(const char *str, int *res)
{
	char *ptr;
	long val = strtol(str, &ptr, 10);
	
	if (str == ptr || *ptr != '\0' || val < INT_MIN || val > INT_MAX)
	{
		return (1);
	}
	*res = (int) val;
	return (0);
}
