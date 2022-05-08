#include "shell.h"

/**
 * free_double_ptr - frees  memory allocated to a double pointer
 * @ptr: Pointer to address to be freed
 * @len: size
 * Return: void
 */

void free_double_ptr(char **ptr, int len)
{
	int i;

	if (len == 0)
		return;
	for (i = 0; i < len; i++)
		free(ptr[i]);
	free(ptr);
}

/**
 * free_double_ptr2 - frees  memory allocated to a double pointer that is
 * NULL terminated
 * @ptr: Pointer to address to be freed
 * Return: void
 */

void free_double_ptr2(char **ptr)
{
	int i  = 0;

	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
