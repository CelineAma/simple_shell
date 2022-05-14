#include "shell.h"

void sigint_handler(__attribute__((unused)) int sig_num)
{
	write(STDOUT_FILENO, "\n$ ", 3);
	signal(SIGINT, sigint_handler);
}
/**
 * main - Entry point
 * @argc: Number of command line arugment
 * @argv: Array of command line argument
 * Return: 0
 */

int main(int argc, char *argv[])
{
	char *prompt = "$ ", *buffer = NULL;
	int len = 0, ret = 0;

	name = argv[0], environ = init_env(), aliases = NULL, line_number = 0;
	signal(SIGINT, sigint_handler);
	if (argc > 1)
	{
	}
	else if (!isatty(STDIN_FILENO))
	{
		while (1)
		{
			ret = _getline(&buffer, &len, STDIN_FILENO);
			line_number++;
			if (len > 0)
				handle_line(buffer);
			if (ret == EOF)
				break;
		}
	}
	else
	{
		while (1)
		{
			write(STDOUT_FILENO, prompt, _strlen(prompt));
			ret = _getline(&buffer, &len, STDIN_FILENO);
			line_number++;
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
	free_alias(&aliases);
	return (0);
}