#include "shell.h"

/**
 * remove_env - Unsets an enviromental vairable
 * @name: name of the environmental variable
 * Return: 0 if it succeds , -1 if it fails
 */

int remove_env(char *name)
{
	int size = 0, i = 0;
	char **new_environ;

	if (get_env(name) == NULL)
		return (0);
	while (environ[size])
	{
		if (!_strncmp(environ[size], name, _strlen(name))
		&& environ[size][_strlen(name)] == '=')
			i = size;
		size++;
	}
	new_environ = malloc(sizeof(char *) * (size));
	if (new_environ == NULL)
		return (-1);
	_memcpy(new_environ, environ, i);
	free(environ[i]);
	_memcpy(new_environ + i, environ + i + 1, size - i);
	free(environ);
	new_environ[size - 1] = NULL;
	environ = new_environ;
	return (0);
}

/**
 * print_env - Prints all env
 * @command: input command
 * @all_args: Pointer to the an array of other argurments
 * Return: 0 if successful else 1
 */

int print_env(char **command, __attribute__((unused))char **all_args)
{
	int i = 0;

	while (command[i])
		i++;
	if (i > 1)
		return (-1);
	print_all_env();
	return (0);
}

/**
 * set_env - Sets an environmental variable
 * @command: Input command
 * @all_args: Pointer to the an array of other argurments
 * Return: 0 if succeccful else -1
 */

int set_env(char **command, __attribute__((unused))char **all_args)
{
	int i = 0;

	while (command[i])
		i++;
	if (i  != 3)
		return (-1);
	if (add_env(command[1], command[2]) == NULL)
		return (-1);
	else
		return (0);
}

/**
 * unset_env - unsets an environmental variable
 * @command: Input command
 * @all_args: Pointer to the an array of other argurments
 * Return: 0 if successful else -1
 */

int unset_env(char **command, __attribute__((unused))char **all_args)
{
	int i = 0;

	while (command[i])
		i++;
	if (i > 2)
		return (-1);
	if (!remove_env(command[1]))
		return (0);
	return (-1);
}


