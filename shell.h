#ifndef SHELL
#define SHELL

#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <linux/limits.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

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

/**
 * func_t - Typedef of a function pointer that returns an integer and
 * takes a double pointer as an argument
 */

typedef int (*func_t)(char **command, char **all_args);

/**
 * struct builtin_s - A struct that holds the name of builtin operation
 * and a pointer to the operation itself
 * @name: Name of the builtin operation
 * @func: Pointer to the builtin operation
 */

typedef struct builtin_s
{
	char *name;
	func_t func;
} builtin_t;

/* Environmental Variable of the shell */
extern char **environ;

/* Line counter */
unsigned int line_number;

/* Global aliases variable to hold all alias */
alias_t *aliases;

/* Global file name */
char *name;

/* Process id */
pid_t pid;

/* Exit status of last process*/
int last_exit_status;

/* File descriptor for input file */
int fd;

/* Linked list for PATH variable */

/* String operations */
int _strlen(char *str);
char **_split(char *str, char delim);
char *_strdup(char *str);
char *str_concat(char *s1, char *s2, char *s3);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcpy(char *dest, char *src);
int _strncmp(char *s1, char *s2, int n);
char *int_to_str(int number);
char **_split2(char *str, char delim);

/* Input operations */
int _getline(char **buffer, int *size, int fd);
int _getline2(char **buffer, int *len, int fd);
char **split_line(char *str);
void handle_line(char *bufer);
int handle_comments(char *buffer);

/* Env operations */
char **init_env(void);
char *get_env(char *name);
void print_all_env(void);
char *add_env(char *name, char *value);
void replace_envs(char **command);
int remove_env(char *name);
void replace_special_envs(char **command);

/* Alias operation */
alias_t *add_alias(char *name, char *value);
void free_alias(alias_t **head);
char *get_alias(char *name);
void replace_alias(char **command);
int remove_alias(char *name);
int is_valid_alias_op(char *arg);

/* Memory operations */
void *_realloc1(void *ptr, unsigned int old_size, unsigned int new_size);
void *_realloc2(char **ptr, unsigned int old_size, unsigned int new_size);
char **_memcpy(char **dest, char **src, unsigned int n);
char *_memcpy2(char *dest, char *src, unsigned int n);
void free_double_ptr2(char **ptr);
void free_double_ptr(char **ptr, int len);

/* Builtin operation */
func_t get_builtin(char **command);
int print_env(char **command, char **all_args);
int set_env(char **command, char **all_args);
int unset_env(char **command, char **all_args);
int alias(char **command, char **all_args);
int exit_shell(char **command, char **all_args);
int cd(char **command, char **all_args);

/* Command operations */
int handle_args(char *args, char **all_args);

/* Path operations */
int replace_with_path(char **args, char **command);

/* Helpers */
int check_count(char *stsr, int i, int *next);
int is_str_num(char *str);
int _isdigit(int c);
int _split_helper(char *str, int i, char delim);

int execute(char *command, char **args, char **all_args);

/* Errors Helpers */
int create_alias_error(char *alias_name);
int create_command_error(int err_code, char *command);
int create_exit_error(char *input);
int create_cd_error(char *input);
int create_file_error(char *filename);

/* Output operations */
int output_alias(char *alias_name, char *alias_value);
void output_env(char *str);

/* Modes */
void interactive_mode(void);
void non_interactive_mode(void);
int file_mode(char *filename);

#endif /* SHELL */
