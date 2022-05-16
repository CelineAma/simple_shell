#include "shell.h"

/**
 * remove_alias - Removes an alias
 * @name: Name of the alias to be removed
 * Return: 0 if it succeds or -1 if it fails
 */

int remove_alias(char *name)
{
	int ret_val = -1, i = 0;
	alias_t *current = aliases, *prev = aliases, *temp;

	while (current)
	{
		if (!_strcmp(name, current->name))
		{
			temp = current->next;
			current->next = NULL;
			free_alias(&current);
			ret_val = 0;
			if (i == 0)
				aliases = temp;
			else
				prev->next = temp;
			break;
		}
		i++;
		prev = current;
		current = current->next;
	}
	return (ret_val);
}

/**
 * is_valid_alias_op - checks if a string is a valid alias operation
 * @arg: input string
 * Return: 0 if not valid else position of '=' in the string
 */

int is_valid_alias_op(char *arg)
{
	int i = 0;

	while (arg[i])
	{
		if (arg[i] == '=')
			break;
		i++;
	}

	if (i == _strlen(arg) || i == _strlen(arg) - 1)
		return (0);
	else
		return (i);
}

/**
 * alias - Performs the alias built in operation
 * @command: input command
 * @all_args: pointer to all the remaining args
 * Return: 0 if successful else -1
 */

int alias(char **command, __attribute__((unused)) char **all_args)
{
	int ret_val, i = 1, temp, error = 0;
	char *temp_;

	while (command[i])
	{
		temp = is_valid_alias_op(command[i]);
		if (temp)
		{
			command[i][temp] = 0;
			if (add_alias(command[i], command[i] + temp + 1) != NULL)
				ret_val = 0;
			command[i][temp] = '=';
		}
		else
		{
			temp_ = get_alias(command[i]);
			if (temp_ != NULL)
				error = output_alias(command[i], temp_);
			else
				error = create_alias_error(command[i]);
		}
		i++;
	}
	ret_val = error ? error : ret_val;
	return (ret_val);
}
