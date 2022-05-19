#include "shell.h"

/**
 * sigint_handler - Prevents the program from terminating unexpectedly from
 * Ctrl - c
 * @sig_num: input signal
 * Return: void
 */

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
	name = argv[0], environ = init_env(), aliases = NULL, line_number = 0;
	pid = getpid(), last_exit_status = 0, fd = 0;

	signal(SIGINT, sigint_handler);
	if (argc > 1)
		last_exit_status = file_mode(argv[1]);
	else if (!isatty(STDIN_FILENO))
		non_interactive_mode();
	else
		interactive_mode();
	free_double_ptr2(environ);
	free_alias(&aliases);
	return (last_exit_status);
}
