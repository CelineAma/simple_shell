#include "shell.h"

/**
 * _strdup - dupliates a string
 * @str: string to be duplicated
 * Return: pointer to duplicated string
 */

char *_strdup(char *str)
{
	char *dup;
	int i;

	if (str == NULL)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * _strlen(str) + 1);
	if (dup == NULL)
		return (NULL);
	for (i = 0; i < _strlen(str); i++)
	{
		dup[i] = str[i];
	}
	dup[i] = '\0';
	return (dup);
}

/**
 * str_concat - joins to strings
 * @s1: string one
 * @s2: string two
 * Return: pointer to concatenated string
 */

char *str_concat(char *s1, char *s2)
{
	int i, j, length;
	char *res;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	i = 0;
	j = 0;
	length = _strlen(s1) + _strlen(s2) + 1;
	res = (char *)malloc(sizeof(char) * length);
	if (res == NULL)
		return (NULL);
	while (s1[i])
	{
		res[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		res[j] = s2[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}

/**
 * _strncpy - copy source to dest by n amount
 * @dest: destination string
 * @src: source string
 * @n: amount to copy
 * Return: pointer to the destination string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, j = _strlen(src);

	for (i = 0; i < n; i++)
	{
		if (i < j)
			dest[i] = src[i];
		else
			dest[i] = 0;
	}
	return (dest);
}

/**
 * _strncat - concatenates two strings by a required amout
 * @dest: destination string
 * @src: source string
 * @n: amount to concenate
 * Return: pointer to dest
 */

char *_strncat(char *dest, char *src, int n)
{
	int j, i = 0;

	while (1)
	{
		if (dest[i] == '\0')
		{
			j = 0;
			while (src[j] && j < n)
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

/**
 * _strncmp - compares two strings by a number of bytes
 * @s1: first string
 * @s2: second string
 * @n: the number of bytes to compares
 * Return: 0 if the same else returns the difference
 */

int _strncmp(char *s1, char *s2, int n)
{
	int i = 0;

	while (s1[i] && s2[i] && i < n)
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
