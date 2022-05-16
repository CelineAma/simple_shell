#include "shell.h"

/**
 * int_to_str - Converts an number to a string
 * @number: input number
 * Return: Pointer to the created string of NULL if it fails
 */

char *int_to_str(int number)
{
	int size = 1, dup_number, i = 0, is_neg = 0;
	char *ret_val;

	if (number == 0)
	{
		ret_val = _strdup("0");
		return (ret_val);
	}
	if (number < 0)
	{
		size++;
		number *= -1;
		is_neg = 1;
	}
	dup_number = number;
	while (dup_number / 10)
	{
		size++;
		dup_number /= 10;
	}
	ret_val = malloc(sizeof(char) * (size + 1));
	if (ret_val == NULL)
		return (NULL);
	ret_val[size--] = 0;
	if (is_neg)
		ret_val[i++] = '-';
	while (size >= i)
	{
		ret_val[size--] = (number % 10) + '0';
		number /= 10;
	}
	return (ret_val);
}

/**
 * _split_helper - checks for '"' or "'"
 * @str: input string
 * @i: current iteration count
 * @delim: delim to be used for the split
 * Return: The number of characters before the next delim
 */

int _split_helper(char *str, int i, char delim)
{
	int flag = 0, count = 0;

	while (str[i] != delim && str[i] != 0)
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			flag = str[i];
			i++;
			while (str[i] != flag)
			{
				i++;
				count++;
			}
			i++;
			continue;
		}
		i++;
		count++;
	}
	return (count);
}

/**
 * _split2 - Splits a string by the @delim provided
 * @str: input string
 * @delim: delimeter
 * Return: A double pointer to the strings or NULL if it fails
 */

char **_split2(char *str, char delim)
{
	char **ret_val = NULL;
	int i = 0, len = 0, count;
	char *val, flag = 0;

	if (!str)
		return (ret_val);
	while (str[i])
	{
		if (str[i] == delim)
		{
			i++;
			continue;
		} count = _split_helper(str, i, delim);
		val = malloc(sizeof(char) * (count + 1));
		if (val == NULL)
			return (NULL);
		count = 0;
		while (str[i] != delim && str[i] != 0)
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				flag = str[i++];
				while (str[i] != flag)
					val[count++] = str[i++];
				i++;
				continue;
			} val[count++] = str[i++];
		} val[count] = 0;
		ret_val = _realloc2(ret_val, sizeof(char *)
		* len, sizeof(char *) * (len + 1));
		if (ret_val == NULL)
			return (ret_val);
		ret_val[len++] = val;
	}
	if (len > 0)
	{
		ret_val = _realloc2(ret_val, sizeof(char *)
		* len, sizeof(char *) * (len + 1));
		ret_val[len] = NULL;
	} return (ret_val);
}
