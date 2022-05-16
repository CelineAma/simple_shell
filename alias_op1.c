#include "shell.h"

/**
 * add_alias - Adds a new alias or overwrite the existing one
 * @name: Name of the alias
 * @value: The value of the alias
 * Return: Pointer to the added alias
 */

alias_t *add_alias(char *name, char *value)
{
	alias_t *new_alias, *current = aliases, *prev;

	new_alias = malloc(sizeof(alias_t));
	if (new_alias == NULL)
		return (NULL);
	new_alias->name = _strdup(name);
	new_alias->value = _strdup(value);
	new_alias->next = NULL;
	if (current == NULL)
	{
		aliases = new_alias;
		return (new_alias);
	}
	else
	{
		while (current != NULL)
		{
			if (!_strcmp(current->name, name))
			{
				free(current->value);
				current->value = _strdup(value);
				free_alias(&new_alias);
				return (current);
			}
			prev = current;
			current = current->next;
		}
		prev->next = new_alias;
		return (new_alias);
	}
}

/**
 * free_alias - Frees alias_t linked list
 * @head: Pointer to the head of the alias_t list
 * Return: void
 */

void free_alias(alias_t **head)
{
	alias_t *next, *current;

	if (head == NULL)
		return;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	*head = NULL;
}


/**
 * get_alias - Gets the value of an alias
 * @name: Name of the alias
 * Return: The value of the alias of NULL if not found
 */

char *get_alias(char *name)
{
	char *ret_val = NULL;
	alias_t *current = aliases;

	while (current)
	{
		if (!_strncmp(current->name, name, _strlen(name))
		&& current->name[_strlen(name)] == 0)
		{
			ret_val = current->value;
			break;
		}
		current = current->next;
	}
	return (ret_val);
}

/**
 * replace_alias - Checks all arguments of a command and replaces
 * it if there is an alias that matches it
 * @command: The input command which is an array of strings
 * Return: void
 */

void replace_alias(char **command)
{
	int i = 0;
	char *alias;

	while (command[i])
	{
		alias = get_alias(command[i]);
		if (alias != NULL)
		{
			free(command[i]);
			command[i] = _strdup(alias);
		}
		/* Remove later */
		if (!_strncmp(command[i], "alias", _strlen("alias")))
			break;
		i++;
	}
}
