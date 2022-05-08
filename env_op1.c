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
		if (!_strncmp(environ[i], name, _strlen(name)))
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
		env[i] = strdup(environ[i]);
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
