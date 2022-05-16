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

/**
 * is_str_num - checks if a string is a number
 * @str: input string
 * Return: 1 if string is a number else 0
 */

int is_str_num(char *str)
{
	int i = 0, ret_val = 1;

	if (str[i] && str[i] == '+')
		i++;
	while (str[i])
	{
		if (_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (ret_val);
}

/**
 * _isdigit - checks if a character is digit
 * @c: carrier variable
 * Return: 1 if true, 0 if false
 */

int _isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);

	else
		return (0);
}
