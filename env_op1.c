#include "shell.h"

/**
 * get_env - Gets the value of the env provided
 * @name: name of the env
 * Return: pointer to the env of NULL if not found
 */

char *get_env(char *name)
{
	int i = 0;
	char *ret_val = NULL;

	while (environ[i])
	{
		if (!_strncmp(environ[i], name, _strlen(name))
		&& environ[i][_strlen(name)] == '=')
		{
			ret_val = environ[i] + _strlen(name) + 1;
			return (ret_val);
		}
		i++;
	}
	return (ret_val);
}

/**
 * init_env - Copies the env to the environ variable
 * Return: Pointer the all the envs
 */

char **init_env(void)
{
	char **env;
	int size = 0, i = 0;

	while (environ[size])
		size++;

	env = malloc(sizeof(char *) * (size + 1));
	if (env == NULL)
		return (NULL);
	for (i = 0; i < size; i++)
	{
		env[i] = _strdup(environ[i]);
		if (env[i] == NULL)
		{
			free_double_ptr(env, i);
			exit(2);
			/* Create error here */
		}
	}
	env[i] = NULL;
	return (env);
}

/**
 * print_all_env - Prints out all the environment variable
 * Return: void
 */

void print_all_env(void)
{
	int i = 0;

	while (environ[i])
		output_env(environ[i++]);
}

/**
 * add_env - Adds an environmental variable or replaces an existing
 * one
 * @name: Name of the environmental variable
 * @value: The value of the environmental variable
 * Return: A pointer to the added environmental variable or NULL
 * if it fails
 */

char *add_env(char *name, char *value)
{
	char **new_environ, *new_env, *delim = "=";
	int size = 0, i = 0;

	new_env = malloc(sizeof(char) * (_strlen(name) + _strlen(value) + 2));
	if (new_env == NULL)
		return (NULL);
	_strncpy(new_env, name, _strlen(name));
	i += _strlen(name);
	_strncpy(new_env + i, delim, _strlen(delim));
	i += _strlen(delim);
	_strncpy(new_env + i, value, _strlen(value));
	i += _strlen(value);
	new_env[i] = 0;
	while (environ[size])
		size++;
	if (get_env(name) == NULL)
	{
		new_environ = malloc(sizeof(char *) * (size + 2));
		if (new_environ == NULL)
		{
			free(new_env);
			return (NULL);
		} _memcpy(new_environ, environ, size);
		new_environ[size++] = new_env;
		new_environ[size] = NULL;
		free(environ);
		environ = new_environ;
	} else
	{
		size = 0;
		while (environ[size])
		{
			if (!_strncmp(environ[size], name, _strlen(name)))
			{
				free(environ[size]);
				environ[size] = new_env;
				break;
			} size++;
		}
	} return (new_env);
}

/**
 * replace_envs - Checks all argument of a command and replaces it
 * if there is an env that matches it else it removes it
 * @command: The input command which is an array of strings
 * Return: void
 */

void replace_envs(char **command)
{
	int i = 0, j;
	char *env;

	while (command[i])
	{
		if (command[i][0] == '$')
		{
			env = get_env(command[i] + 1);
			if (env != NULL)
			{
				free(command[i]);
				command[i] = _strdup(env);
			}
			else
			{
				free(command[i]);
				j = i + 1;
				command[i] = command[j];
				while (command[j])
				{
					command[j] = command[j + 1];
					j++;
				}

			}
		}
		i++;
	}
}

