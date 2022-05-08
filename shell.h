#ifndef SHELL
#define SHELL

#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

/**
 * struct alias_s - A struct that holds the name and value of an alias and a
 * pointer to the next one
 * @name: The name of the alias
 * @value: The value of the alias
 * @next: A pointer to the next alias
 */

typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Environmental Variable of the shell */
extern char **environ;

/* Line counter */
unsigned int line_number;

/* Global aliases variable to hold all alias */
alias_t *aliases;

/* Global file name */
char *name;

/* Linked list for PATH variable */

/* String operations */
int _strlen(char *str);
char **_split(char *str, char delim);
char *_strdup(char *str);
char *str_concat(char *s1, char *s2);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
int _strncmp(char *s1, char *s2, int n);

/* Input operations */
int _getline(char **buffer, int *size, int fd);
char **split_line(char *str);
void handle_line(char *bufer);

/* Env operations */
char **init_env(void);
char *get_env(char *name);

/* Memory operations */
void *_realloc1(void *ptr, unsigned int old_size, unsigned int new_size);
void *_realloc2(char **ptr, unsigned int old_size, unsigned int new_size);
char **_memcpy(char **dest, char **src, unsigned int n);
char *_memcpy2(char *dest, char *src, unsigned int n);
void free_double_ptr2(char **ptr);
void free_double_ptr(char **ptr, int len);

/* Command operations */
int handle_args(char *args, char **all_args);

/* Helpers */
int check_count(char *stsr, int i, int *next);

int execute(char *str);
#endif /* SHELL */
