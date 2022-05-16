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
		*buffer = (void *)_realloc1(*buffer, (*len) - 1, sizeof(char)
		* ((*len) + 1));
		if (*buffer == NULL)
			return (-2);
		(*buffer)[(*len) - 1] = temp;
		(*buffer)[*len] = 0;
		read_ret = read(fd, &temp, 1);
	}
	if (read_ret == -1)
		return (7);
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
		ret_val = _realloc2(ret_val, sizeof(char *) * len, sizeof(char *)
		* (len + 1));
		if (ret_val == NULL)
			return (NULL);
		ret_val[len] = malloc(sizeof(char) * (count + 1));
		if (ret_val[len] == NULL)
		{
			free_double_ptr(ret_val, len);
			return (NULL);
		} _strncpy(ret_val[len], str + i, count);
		ret_val[len++][count] = 0;
		if ((i + count) >= (int)_strlen(str))
		{
			i += count;
			break;
		} ret_val = _realloc2(ret_val, sizeof(char *) * len, sizeof(char *)
		 * (len + 1));
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
	} ret_val = _realloc2(ret_val, sizeof(char *) * len, sizeof(char *)
	* (len + 1));
	if (ret_val == NULL)
		return (NULL);
	ret_val[len] = NULL;
	return (ret_val);
}

/**
 * handle_comments - Handles comments in commands
 * @buffer: user input
 * Return: 1 if comment at beginning of the command else 0
 */

int handle_comments(char *buffer)
{
	int i = 0;

	while (buffer[i])
	{
		if ((buffer[i] == '#' && i == 0) || (buffer[i] == '#'
		&& buffer[i - 1] == ' '))
		{
			buffer[i] = 0;
			break;
		}
		i++;
	}
	if (!buffer[0])
	{
		free(buffer);
		return (1);
	}
	return (0);
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

	if (handle_comments(buffer))
		return;
	split = split_line(buffer);
	free(buffer);
	if (split == NULL)
		return;
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
		} else if (!_strcmp(split[i], "&&"))
		{
			if (!ret_val)
				i++;
			else
				i += 2;
			if (i >= size)
				break;
			continue;
		} else if (!_strcmp(split[i], ";"))
		{
			i++;
			continue;
		} ret_val = handle_args(split[i++], split);
		last_exit_status = ret_val;
	} free_double_ptr(split, size);
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
	replace_special_envs(splited_args);
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
		ret_val = create_command_error(127, splited_args[0]);
		free_double_ptr2(splited_args);
		return (ret_val);
	}
	ret_val = execute(temp, splited_args, all_args);
	free(temp);
	free_double_ptr2(splited_args);
	return (ret_val);
}


