#include "shell.h"

/**
 * check_count - Gets the number of words before "||" or "&&"
 * @str: The string to traverse
 * @i: Current iteration value
 * @next: Pointer to hold the size of the delimeter
 * Return: The number of words before "||" or "&&"
 */

int check_count(char *str, int i, int *next)
{
	int count = 0;

	while (str[i] && _strncmp(str + i, "||", 2) && _strncmp(str + i, "&&", 2)
	&& _strncmp(str + i, ";", 1))
	{
		i++;
		count++;
	}
	if (!_strncmp(str + i, "||", 2) || !_strncmp(str + i, "&&", 2))
		*next = 2;
	else
		*next = 1;
	return (count);
}
