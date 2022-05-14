#include "shell.h"

/**
 * _getline - Gets a line of character from the fd provided
 * @buffer: where to store the line gotten
 * @len: The lenght of the line read
 * @fd: where to read from
 * Return: The number of lines read, -1 if it gets to EOF
 */

int _getline(char **buffer, int *len, int fd)
{
	char temp = 0;
	int read_ret = 0;

	*len = 0;
	*buffer = NULL;
	read_ret = read(fd, &temp, 1);
	while (read_ret >= 0)
	{
		if (temp == 10)
			break;
		if (read_ret == 0 && (*len) == 0)
			break;
		if (read_ret == 0)
		{
			read_ret = read(fd, &temp, 1);
			continue;
		}
		(*len)++;
		*buffer = (void *)_realloc1(*buffer, (*len) - 1, sizeof(char) * ((*len) + 1));
		if (*buffer == NULL)
			return (-2);
		(*buffer)[(*len) - 1] = temp;
		(*buffer)[*len] = 0;
		read_ret = read(fd, &temp, 1);
	}
	if (read_ret == 0 && (*len) == 0)
		return (EOF);
	return (*len);
}

/**
 * split_line - splits a string using "||" or "&&" or ";"
 * @str: input string
 * Return: An array of strings
 */

char **split_line(char *str)
{
	int i = 0, count, len = 0, next = 0;
	char **ret_val = NULL;

	while (str[i])
	{
		count = check_count(str, i, &next);
		ret_val = _realloc2(ret_val, sizeof(char *) * len, sizeof(char *) * (len + 1));
		if (ret_val == NULL)
			return (NULL);
		ret_val[len] = malloc(sizeof(char) * (count + 1));
		if (ret_val[len] == NULL)
		{
			free_double_ptr(ret_val, len);
			return (NULL);
		}
		_strncpy(ret_val[len], str + i, count);
		ret_val[len++][count] = 0;
		if ((i + count) >= (int)_strlen(str))
		{
			i += count;
			break;
		}
		ret_val = _realloc2(ret_val, sizeof(char *) * len, sizeof(char *) * (len + 1));
		if (ret_val == NULL)
			return (NULL);
		ret_val[len] = malloc(sizeof(char) * (next + 1));
		if (ret_val[len] == NULL)
		{
			free_double_ptr(ret_val, len);
			return (NULL);
		}
		_strncpy(ret_val[len], str + i + count, next);
		ret_val[len++][next] = 0;
		i += count + next;
	}
	ret_val = _realloc2(ret_val, sizeof(char *) * len, sizeof(char *) * (len + 1));
	if (ret_val == NULL)
		return (NULL);
	ret_val[len] = NULL;
	return (ret_val);
}

/**
 * handle_line - Handles seperation of lines into commands
 * @buffer: where to get the line from
 * Return: void
 */

void handle_line(char *buffer)
{
	char **split;
	int i = 0, ret_val, size = 0;

	while (buffer[i])
	{
		if (buffer[i] == '#')
		{
			buffer[i] = 0;
			break;
		}
		i++;
	}
	if (!buffer[0])
	{
		free(buffer);
		return;
	}
	i = 0;
	split = split_line(buffer);
	free(buffer);
	if (split == NULL)
	{
		/* create error here */
		return;
	}
	while (split[size])
		size++;
	while (split[i])
	{
		if (!_strcmp(split[i], "||"))
		{
			if (ret_val)
				i++;
			else
				i += 2;
			if (i >= size)
				break;
			continue;
		}
		else if (!_strcmp(split[i], "&&"))
		{
			if (!ret_val)
				i++;
			else
				i += 2;
			if (i >= size)
				break;
			continue;
		}
		else if (!_strcmp(split[i], ";"))
		{
			i++;
			continue;
		}
		ret_val = handle_args(split[i++], split);
		add_env("?", "3");
	}
	free_double_ptr(split, size);
}

/**
 * handle_args - handles a single command
 * @args: The command
 * @all_args: Pointer to the start of the remaining commmands
 * Return: The exit status of the command
 */

int handle_args(char *args, __attribute__((unused)) char **all_args)
{
	char **splited_args, *temp = NULL;
	int ret_val = 0;
	func_t builtin;

	splited_args = _split(args, ' ');
	if (splited_args == NULL) /* Create error here */
		return (-2);
	replace_alias(splited_args);
	if (!splited_args[0])
	{
		free_double_ptr2(splited_args);
		return (1);
	}
	replace_envs(splited_args);
	builtin = get_builtin(splited_args);
	if (builtin != NULL)
	{
		ret_val = builtin(splited_args, all_args);
		free_double_ptr2(splited_args);
		return (ret_val);
	}
	if (replace_with_path(splited_args, &temp))
	{
		dprintf(STDERR_FILENO, "%s: %d: %s: not found\n", name, line_number, splited_args[0]);
		free_double_ptr2(splited_args);
		return (1);
	}
	ret_val = execute(temp, splited_args, all_args);
	free(temp);
	free_double_ptr2(splited_args);
	return (ret_val);
}

int execute(char *command, char **args, char **all_args)
{
	pid_t pid;
	int ret_val;

	pid = fork();
   if (pid == -1)
      return (1);
	if (pid == 0)
	{
		errno = 0;
		execve(command, args, environ);
		if(errno == EACCES)
			dprintf(STDERR_FILENO, "%s: %d: %s: Permission denied\n", name, line_number, command);
		free(command);
		free_double_ptr2(args);
		free_double_ptr2(all_args);
		free_double_ptr2(environ);
		free_alias(&aliases);
		_exit(1);
	}
	else
	{
		wait(&ret_val);
		ret_val = WEXITSTATUS(ret_val);
	}
	return (ret_val);
}
