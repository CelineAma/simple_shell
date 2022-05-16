#include "shell.h"


/**
 * interactive_mode - Handles the use of this program interactively
 */

void interactive_mode(void)
{
	char *prompt = "$ ", *buffer = NULL;
	int len = 0, ret = 0;

	while (1)
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));
		ret = _getline(&buffer, &len, STDIN_FILENO);
		line_number++;
		if (len > 0)
			handle_line(buffer);
		if (ret == EOF)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
	}
}

/**
 * non_interactive_mode - Handles the use of this program non
 * interactively
 */

void non_interactive_mode(void)
{
	char *buffer = NULL;
	int len = 0, ret = 0;

	while (1)
	{
		ret = _getline2(&buffer, &len, STDIN_FILENO);
		line_number++;
		if (len > 0)
			handle_line(buffer);
		if (ret == EOF)
			break;
	}
}

/**
 * file_mode - Handles the use of this program when a second argument
 * is passed to it
 * @filename: name of the second argument, the file to be executed
 * Return: 127 if it fails to open the file, 5 if it fails to close the
 * file and 0 if everything goes fine
 */

int file_mode(char *filename)
{
	char *buffer = NULL;
	int len = 0, ret = 0;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ret = create_file_error(filename);
		return (ret);
	}
	name = filename;
	while (1)
	{
		ret = _getline2(&buffer, &len, fd);
		line_number++;
		if (len > 0)
			handle_line(buffer);
		if (ret == EOF)
			break;
	}
	if (close(fd) == -1)
		return (5);
	return (0);
}
