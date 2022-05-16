#include "shell.h"

/**
 * execute - Handles executing of commands
 * @command: command name
 * @args: command arguments
 * @all_args: pointer to the remaining commands passed so ther can be
 * freed
 * Return: The exit status of the command
 */

int execute(char *command, char **args, char **all_args)
{
	pid_t pid;
	int ret_val = 1;

	pid = fork();
	if (pid == -1)
		return (5);
	if (pid == 0)
	{
		errno = 0;
		execve(command, args, environ);
		if (errno == EACCES)
			ret_val = create_command_error(126, command);
		free(command);
		free_double_ptr2(args);
		free_double_ptr2(all_args);
		free_double_ptr2(environ);
		free_alias(&aliases);
		_exit(ret_val);
	}
	else
	{
		wait(&ret_val);
		ret_val = WEXITSTATUS(ret_val);
	}
	return (ret_val);
}
