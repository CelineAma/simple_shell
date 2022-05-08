#include "shell.h"

/**
 * _realloc1 - Allocates memory from old_size to new_size
 * @ptr: pointer to hold address of allocated memory
 * @old_size: old_size
 * @new_size: new_size
 * Return: Address of allocated memory or NULL if it fails
 */

void *_realloc1(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new;

	if (old_size == new_size)
		return (ptr);
	if (ptr != NULL && new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		new = malloc(new_size);
		if (new == NULL)
			return (NULL);
		else
			return ((void *)new);
	}
	new = malloc(new_size);
	if (new == NULL)
		return (NULL);
	_memcpy2(new, ptr, old_size);
	free(ptr);
	return (new);
}

/**
 * _realloc2 - Allocates memory from old_size to new_size
 * @ptr: pointer to hold address of allocated memory
 * @old_size: old_size
 * @new_size: new_size
 * Return: Address of allocated memory or NULL if it fails
 */

void *_realloc2(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **new;

	if (old_size == new_size)
		return (ptr);
	if (ptr != NULL && new_size == 0)
	{
		free_double_ptr(ptr, old_size / sizeof(char *));
		return (NULL);
	}
	if (ptr == NULL)
	{
		new = malloc(new_size);
		if (new == NULL)
			return (NULL);
		else
			return ((void *)new);
	}
	new = malloc(new_size);
	if (new == NULL)
	{
		free_double_ptr(ptr, old_size / sizeof(char *));
		return (NULL);
	}
	_memcpy(new, ptr, old_size / sizeof(char *));
	free(ptr);
	return (new);
}

/**
 * _memcpy - copies memory from src to destination(double pointer)
 * @dest: destination
 * @src: source
 * @n: amount to copy
 * Return: address of the destination
 */

char **_memcpy(char **dest, char **src, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

/**
 * _memcpy2 - copies memory from src to destination
 * @dest: destination
 * @src: source
 * @n: amount to copy
 * Return: address of the destination
 */
char *_memcpy2(char *dest, char *src, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
