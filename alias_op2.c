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
 * remove_quote - remove quotes from alias value
 * @input: input string
 * Return: 1 if it find a quote else 0
 */

int remove_quote(char *input)
{
	int ret = 0, i = 0;

	if (input[i] == '\'')
		ret = 1;
	while (input[i])
	{
		if (input[i] == '\'')
			input[i] = 0;
		i++;
	}
	return (ret);
}

/**
 * print_all_alias - Handles printing all aliases
 * @head: Pointer to the head of the alias list
 */

void print_all_alias(alias_t *head)
{
	alias_t *current = head;

	while (current)
	{
		output_alias(current->name, current->value);
		current = current->next;
	}

}
/**
 * alias - Performs the alias built in operation
 * @command: input command
 * @all_args: pointer to all the remaining args
 * Return: 0 if successful else -1
 */

int alias(char **command, __attribute__((unused)) char **all_args)
{
	int ret_val = 0, i = 1, temp, error = 0, k = 1;
	char *temp_;

	while (command[i])
	{
		temp = is_valid_alias_op(command[i]);
		if (temp)
		{
			command[i][temp] = 0;
			if (remove_quote(command[i] + temp + 1))
				k++;
			if (add_alias(command[i], command[i] + temp + k) != NULL)
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
	if (i == 1)
		print_all_alias(aliases);
	ret_val = error ? error : ret_val;
	return (ret_val);
}
