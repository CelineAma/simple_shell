#include "shell.h"

/**
 * _strlen - returns length of a string
 * @s: Pointer to the string
 *
 * Return: length of string
 */

int _strlen(char *s)
{
	int length = 0;

	while (s[length])
		length++;
	return (length);
}

/**
 * _split - Splits a string by the @delim provided
 * @str: input string
 * @delim: delimeter
 * Return: A double pointer to the strings or NULL if it fails
 */

char **_split(char *str, char delim)
{
	char **ret_val = NULL;
	int i = 0, len = 0, count;

	if (!str)
		return (ret_val);
	while (str[i])
	{
		if (str[i] == delim)
		{
			i++;
			continue;
		}
		count = 0;
		while (str[i] != delim && str[i] != 0)
		{
			i++;
			count++;
		}
ret_val = _realloc2(ret_val, sizeof(char *) * len, sizeof(char *) * (len + 1));
		if (ret_val == NULL)
			return (ret_val);
		ret_val[len] = malloc(sizeof(char) * (count + 1));
		if (ret_val[len] == NULL)
		{
			free_double_ptr(ret_val, len);
			return (NULL);
		}
		_strncpy(ret_val[len], str + i - count, count);
		ret_val[len][count] = 0;
		len++;
	}
	if (len > 0)
	{
		ret_val = _realloc2(ret_val, sizeof(char *) * len,
		sizeof(char *) * (len + 1));
		ret_val[len] = NULL;
	}

	return (ret_val);
}

/* Test
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
	return count;
}

char **_split(char *str, char delim)
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
		}
		count = _split_helper(str, i, delim);
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
			}
			val[count++] = str[i++];
		}
		val[count] = 0;
	ret_val = _realloc2(ret_val, sizeof(char *) * len, sizeof(char *) * (len + 1));
		if (ret_val == NULL)
			return (ret_val);
		ret_val[len++] = val;
	}
	if (len > 0)
	{
		ret_val = _realloc2(ret_val,sizeof(char *) * len, sizeof(char *) * (len + 1));
		ret_val[len] = NULL;
	}
	return (ret_val);
}
End of Test */

/**
 * *_strcpy -  copies the string pointed to by src
 * @dest: char type string
 * @src: char type string
 * Description: Copy the string pointed to by pointer src to
 * the buffer pointed to by dest
 * Return: Pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	int i = -1;

	do {
		i++;
		dest[i] = src[i];
	} while (src[i] != '\0');

	return (dest);
}

/**
 * _strcmp - compares two strings
 *  @s1: first string
 *  @s2: second string
 *  Return: 0 if the same else returns the difference
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] == s2[i])
		{
			i++;
			continue;
		}
		return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * Return: pointer to dest string
 */

char *_strcat(char *dest, char *src)
{
	int j, i = 0;

	while (1)
	{
		if (dest[i] == '\0')
		{
			j = 0;
			while (src[j])
			{
				dest[i] = src[j];
				i++;
				j++;
			}
			break;
		}
		i++;
	}
	return (dest);
}
