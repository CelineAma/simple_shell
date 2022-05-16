#include "shell.h"

/**
 * create_env_error - Handles creating env errors
 * @command: The name of the command
 * Return: -1
 */

int create_env_error(char *command)
{
	int size;
	char *line = int_to_str(line_number);
	char *error, *message = "Unable to add/remove from environment\n";

	size = _strlen(name) + _strlen(line) + _strlen(command)
	+ _strlen(message) + 7;
	error = malloc(sizeof(char) * size);
	if (error == NULL)
	{
		free(line);
		return (-1);
	}
	error[0] = 0;
	_strcat(error, name);
	_strcat(error, ": ");
	_strcat(error, line);
	_strcat(error, ": ");
	_strcat(error, command);
	_strcat(error, ": ");
	_strcat(error, message);
	write(STDERR_FILENO, error, size - 1);
	free(line);
	free(error);
	return (-1);
}
