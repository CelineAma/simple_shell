#include "shell.h"

/**
 * _getline2 - Gets a line of character from the fd provided. This second
 * getline function is to handle non_interactive mode and file mode
 * @buffer: where to store the line gotten
 * @len: The lenght of the line read
 * @fd: where to read from
 * Return: The number of lines read, -1 if it gets to EOF
 */

int _getline2(char **buffer, int *len, int fd)
{
	char temp = 0;
	int read_ret;

	*len = 0;
	*buffer = NULL;
	read_ret = read(fd, &temp, 1);
	while (read_ret > 0)
	{
		if (temp == 10)
			break;
		/* Test */
		if ((*len) > 0 && temp == ' ' && temp == (*buffer)[(*len) - 1])
		{
			read_ret = read(fd, &temp, 1);
			continue;
		}
		/* End of test */
		(*len)++;
		*buffer = (void *)_realloc1(*buffer, (*len) - 1, sizeof(char)
		* ((*len) + 1));
		if (*buffer == NULL)
			return (-2);
		(*buffer)[(*len) - 1] = temp;
		(*buffer)[*len] = 0;
		read_ret = read(fd, &temp, 1);
	}
	if (read_ret == 0)
		return (EOF);
	return (*len);
}
