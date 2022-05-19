#include "shell.h"

/**
 * replace_with_path - Handles replacing commands with their full
 * paths
 * @args: The command arguments
 * @command: Pointer to the command name
 * Return: 1 if it fails else 0
 */

int replace_with_path(char **args, char **command)
{
	int ret_val = 1;
	char **paths, *slash = "/", *temp;
	int i = 0;

	if (args[0][0] == '.' || args[0][0] == '/')
	{
		*command = _strdup(args[0]);
		ret_val = access(args[0], F_OK);
		if (ret_val)
			free(*command);
	}
	else
	{
		paths = _split(get_env("PATH"), ':');
		if (paths == NULL)
			return (1);
		while (paths[i])
		{
		temp = str_concat(paths[i++], slash, args[0]);
			if (!access(temp, F_OK))
			{
				*command = temp;
				ret_val = 0;
				break;
			}
			free(temp);
		}
		free_double_ptr2(paths);
	}
	return (ret_val);
}
