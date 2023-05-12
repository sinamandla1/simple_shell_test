#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 1024

#define MAX_TOKENS 100
#define MAX_COMMAND_LENGTH 100

/* FOR ALIAS in BUILTIN2 */
#define MAX_ALIAS_NAME 50
#define MAX_ALIAS_VALUE 100
/**
 * struct Alias - struct for aliases
 * @name: name of alias
 * @val: value of alias
 * @next: ptr to next node
 */
typedef struct Alias
{
	char name[MAX_ALIAS_NAME];
	char val[MAX_ALIAS_VALUE];
	struct Alias *next;
} Alias;

extern Alias *alias_head;

/* for interactive_mode*/
int interact_mode(int stdin_fd);
int isDelimiter(char *str);
int is_alpha(int);
int string_to_int(const char *str, int *result);

/* for builtin1.c */
void _exiting(char *status);
int my_environ(char *details);
int set_environ(char *name, char *value);
int unset_environ(char *vari);

/* for builtin2.c */
int change_dir(int argc, char *argv[]);
void alias_printer(void);
void print_aliases(char *name);
void define_alias(char *name, char *val);

/* for gettheline.c */
char *get_line(int *length, int *position);

/* for Tokenize.c */
void tokenize_command(const char *command, char **tokens, int *token_count);

/* paths.c */
int check_command_exists(const char *command);
int execute_command(char *command);

/* vars.c */
char *replace_vars(char *str);
int execute_vars(char *command);

#endif
