#include "shell.h"
/**
 * change_dir - Changes the current directory of the process
 * @argc: number if arg
 * @argv: ptr to an array of strings.
 * Return: 0 or 1 if an error occurs
 */
int change_dir(int argc, char *argv[])
{
	char *dir, *updt_cwd;

	if (argc == 1)
	{
		*dir = getenv("HOME");
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		*dir = getenv("OLDPWD");
	}
	else
	{
		*dir = argv[1];
	}
	updt_cwd = getcwd(NULL, 0);
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", updt_cwd, 1);
	free(updt_cwd);
	return (0);
}

/**
 * alias_printer - prints all aliases
 * Return: void
 */
void alias_printer(void)
{
	Alias *alias_head = NULL;
	Alias *current_node = alias_head;

	while (current_node != NULL)
	{
		printf("%s = '%s'\n", current_node->name, current_node->val);
		current_node = current_node->next;
	}
}

/**
 * print_aliases - prints the value of the alias
 * @name: the name of the alias
 * Return: void
 */
void print_aliases(char *name)
{
	Alias *current_node = alias_head;

	while (current_node != NULL)
	{
		if (strcmp(current_node->name, name) == 0)
		{
			printf("%s='%s'\n", current_node->name, current_node->val);
			return;
		}
		current_node = current_node->next;
	}
	printf("alias: %s: not found\n", name);
	exit(1);
}

/**
 * alias_define - defines the alias
 * @name: name of the alias
 * @val: value of alias
 */
void alias_define(char *name, char *val)
{
	Alias *current_node = alias_head;
	Alias *new_alias = malloc(sizeof(Alias));

	while (current_node != NULL)
	{
		if (strcmp(current_node->name, name) == 0)
		{
			strncpy(current_node->val, val, MAX_ALIAS_VALUE);
			return;
		}
		current_node = current_node->next;
	}
	if (new_alias == NULL)
	{
		perror("malloc");
		exit(1);
	}
	strncpy(new_alias->name, name, MAX_ALIAS_NAME);
	strncpy(new_alias->val, val, MAX_ALIAS_VALUE);
	new_alias->next = alias_head;
	alias_head = new_alias;
}

/**
 * _myalias - entry point
 * @argv: dbl pointer command arguments
 * Return: Always 0
 */
int _myalias(char **argv)
{
	int i = 0;
	char *x = NULL;

	if (argv[1] == NULL)
	{
		alias_printer();
		return (0);
	}
	for (i = 1; argv[i]; i++)
	{
		x = strchr(argv[i], '=');
		if (x)
		{
			alias_define(argv[i], x + 1);
		}
		else
		{
			print_aliases(argv[i]);
		}
	}
	return (0);
}
