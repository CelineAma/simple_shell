#include "shell.h"

/**
 * output_alias - Handles printing of an alias to the stdout
 * @alias_name: alias name
 * @alias_value: alias value
 * Return: 0 if succcessful else 1
 */

int output_alias(char *alias_name, char *alias_value)
{
	int size = _strlen(alias_name) + _strlen(alias_value) + 5;
	char *output = malloc(sizeof(char) * size);

	if (output == NULL)
		return (1);
	output[0] = 0;
	_strcat(output, alias_name);
	_strcat(output, "=\'");
	_strcat(output, alias_value);
	_strcat(output, "\'\n");
	write(STDOUT_FILENO, output, size - 1);
	free(output);
	return (0);
}

/**
 * output_env - Handles printing of an env to the stdout
 * @env: the env to be printed
 * Return: void
 */

void output_env(char *env)
{
	int len = _strlen(env);

	write(STDOUT_FILENO, env, len);
	write(STDOUT_FILENO, "\n", 1);
}
