#include "shell.h"

/**
 * main - entry function
 * @argc: number of args passed
 * @argv: array of argument
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	char *cmd = NULL;
	int status = 0;
	size_t n = 0;

	for (; true;)
	{
		if (isatty(STDIN_FILENO))
			_printf("$");
		if (_getline(&cmd, &n, STDIN_FILENO) == -1)
			free(cmd), exit(status);
		removeLeadingTrailingWhitespace(cmd);
		if (_strlen(_strdup(cmd)) == 0)
			continue;

		if (builtin(cmd) == 1)
			continue;

		else if (builtin(cmd) == 0)
			free(cmd), exit(status);
		if (argc > 0 && _strncmp(cmd, "/bin/", 5) == 0)
		{
			status = path_ls_bin(cmd, argv);
			if (status > 0)
			{
				if (_strncmp(cmd, "/bin/ls", 7) == 0)
					status = 2;
				else
					status = 127;
			}
		}
		else if (argc > 0 && _strncmp(cmd, "/bin/", 5) != 0)
		{
			status = path_ls(cmd, argv);
			if (status > 0)
				status = 127;
		}
	}
	return (0);
}

