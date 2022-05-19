#include "shell.h"

/**
 * cd_helper - Changes directory of the current process
 * @command: the new directory
 * Return: 0 if successful else 1
 */

int cd_helper(char *command)
{
	char buffer[PATH_MAX];

	if (command == NULL)
		return (0);
	add_env("OLDPWD", get_env("PWD"));
	if (chdir(command) == -1)
		return (2);
	if (getcwd(buffer, PATH_MAX) == NULL)
		return (2);
	add_env("PWD", buffer);
	return (0);
}

/**
 * cd - Changes the directory of the current process
 * @command: input command
 * @all_args: pointer to all the remaining args
 * Return: 0 if successful else 1
 */

int cd(char **command, __attribute__((unused)) char **all_args)
{
	DIR *dir;
	int ret_val = 0;
	char *temp;

	if (command[1] == NULL)
		ret_val = cd_helper(get_env("HOME"));
	else
	{
		if ((!_strncmp(command[1], "--", 2) && command[1][2] == 0) ||
			 (!_strncmp(command[1], "-", 1) && command[1][1] == 0))
		{

			if (_strlen(command[1]) == 1)
			{
				temp = _strdup(get_env("OLDPWD"));
				ret_val = cd_helper(temp);
				output_env(get_env("PWD"));
				free(temp);
			}
			else
				ret_val = cd_helper(get_env("HOME"));
		}
		else
		{
			dir = opendir(command[1]);
			if (dir)
			{
				ret_val = cd_helper(command[1]);
				if (closedir(dir) == -1)
					return (10);
			}
			else
				ret_val = create_cd_error(command[1]);
		}
	}
	return (ret_val);
}
