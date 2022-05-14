#include "shell.h"

/**
 * get_builtin - Checks a if a command is a built in operation
 * and returns it of NULL if not found
 * @command: Input command
 * Return: A pointer to a function that returns an int and take
 * a double pointer or NULL if command not found
 */

func_t get_builtin(char **command)
{
	func_t ret_val = NULL;
	int i = 0;
	builtin_t builtin[] = { {"env", print_env}, {"setenv", set_env},
		 {"unsetenv", unset_env}, {"alias", alias}, {"exit", exit_shell},
		 {"cd", cd},
		 {NULL, NULL}};

	while (builtin[i].name)
	{
		if (!_strncmp(command[0], builtin[i].name, _strlen(builtin[i].name)) 
		&& command[0][_strlen(builtin[i].name)] == 0)
		{
			ret_val = builtin[i].func;
			break;
		} i++;
	} return (ret_val);
}

/**
 * exit_shell - handles exiting of the shell
 * @command: input command
 * @all_args: pointer to the remaining args
 * Return: 1 if it fails
 */

int exit_shell(char **command, char **all_args)
{
	int exit_status = 0;

	if (command[1])
	{
		if (is_str_num(command[1]))
			exit_status = atoi(command[1]);
		else
		{
			dprintf(STDERR_FILENO, "%s: %d: %s: Illegal number: %s\n",
			name, line_number, command[0], command[1]);
			return (1);
		}
	}
	free_double_ptr2(command);
	free_double_ptr2(all_args);
	free_double_ptr2(environ);
	free_alias(&aliases);
	exit(exit_status);
}
