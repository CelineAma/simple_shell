#include "shell.h"

/**
 * main - Entry point
 * @argc: Number of command line arugment
 * @argv: Array of command line argument
 * Return: 0
 */


int main(int argc, char *argv[])
{
	char *prompt = "$ ", *buffer;
	int len = 0, ret = 0;

	name = argv[0];
	environ = init_env();
	aliases = NULL;
	if (argc > 1)
	{
	}
	else if (!isatty(STDIN_FILENO))
	{
	}
	else
	{
		while (1)
		{
			write(STDOUT_FILENO, prompt, _strlen(prompt));
			ret = _getline(&buffer, &len, STDIN_FILENO);
			if (len > 0)
				handle_line(buffer);
			if (ret == EOF)
			{
				printf("\n");
				break;
			}
		}
	}
	free_double_ptr2(environ);
	return (0);
}
