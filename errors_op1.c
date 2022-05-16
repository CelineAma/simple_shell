#include "shell.h"

/**
 * create_alias_error - handles creating of alias related errors
 * @alias_name: name of input alias
 * Return: 1
 */

int create_alias_error(char *alias_name)
{
	char *command = "alias: ", *message = " not found\n", *error;
	int size = _strlen(command) + _strlen(message)
	+ _strlen(alias_name) + 1;

	error = malloc(sizeof(char) * size);
	if (error == NULL)
		return (1);
	error[0] = 0;
	_strcat(error, command);
	_strcat(error, alias_name);
	_strcat(error, message);
	write(STDERR_FILENO, error, size - 1);
	free(error);
	return (1);
}

/**
 * create_command_error - handles creating of command related errors
 * @err_code: input error code
 * @command: input command
 * Return: 127 or 126
 */

int create_command_error(int err_code, char *command)
{
	int size;
	char *line = int_to_str(line_number), *message, *error;

	if (line == NULL)
		return (10);
	switch (err_code)
	{
	case 126:
		message = "Permission denied\n";
		break;
	case 127:
		message = "not found\n";
		break;
	}
	size = _strlen(name) + _strlen(line) + _strlen(message)
	 + _strlen(command) + 7;
	error = malloc(sizeof(char) * size);
	if (error == NULL)
	{
		free(line);
		return (10);
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
	return (err_code);
}

/**
 * create_exit_error - Handles exit related errors
 * @input: input
 * Return: 2
 */

int create_exit_error(char *input)
{
	int size;
	char *line = int_to_str(line_number);
	char *error, *message = "Illegal number";

	size = _strlen(name) + _strlen(line) + _strlen("exit")
	+ _strlen(message) + _strlen(input) + 10;
	error = malloc(sizeof(char) * size);
	if (error == NULL)
	{
		free(line);
		return (2);
	}
	error[0] = 0;
	_strcat(error, name);
	_strcat(error, ": ");
	_strcat(error, line);
	_strcat(error, ": ");
	_strcat(error, "exit");
	_strcat(error, ": ");
	_strcat(error, message);
	_strcat(error, ": ");
	_strcat(error, input);
	_strcat(error, "\n");
	write(STDERR_FILENO, error, size - 1);
	free(line);
	free(error);
	return (2);
}

/**
 * create_cd_error - Handles creating cd error
 * @input: input command argument
 * Return: 2
 */

int create_cd_error(char *input)
{
	int size;
	char *line = int_to_str(line_number);
	char *error, *message = "can't cd to ";

	size = _strlen(name) + _strlen(line) + _strlen("cd")
	+ _strlen(message) + _strlen(input) + 8;
	error = malloc(sizeof(char) * size);
	if (error == NULL)
	{
		free(line);
		return (2);
	}
	error[0] = 0;
	_strcat(error, name);
	_strcat(error, ": ");
	_strcat(error, line);
	_strcat(error, ": ");
	_strcat(error, "cd");
	_strcat(error, ": ");
	_strcat(error, message);
	_strcat(error, input);
	_strcat(error, "\n");
	write(STDERR_FILENO, error, size - 1);
	free(line);
	free(error);
	return (2);
}

/**
 * create_file_error - Handles creating file errors
 * @filename: Name of the input file
 * Return: 127
 */

int create_file_error(char *filename)
{
	int size;
	char *line = int_to_str(line_number);
	char *error, *message = "Can't open ";

	size = _strlen(name) + _strlen(line)
	+ _strlen(message) + _strlen(filename) + 6;
	error = malloc(sizeof(char) * size);
	if (error == NULL)
	{
		free(line);
		return (127);
	}
	error[0] = 0;
	_strcat(error, name);
	_strcat(error, ": ");
	_strcat(error, line);
	_strcat(error, ": ");
	_strcat(error, message);
	_strcat(error, filename);
	_strcat(error, "\n");
	write(STDERR_FILENO, error, size - 1);
	free(line);
	free(error);
	return (127);
}
