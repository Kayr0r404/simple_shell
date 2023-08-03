#include "shell.h"

/**
 * builtin - compares exit or env command
 * @cmd: command line from the user
 *
 * Return: errno if exit 1 if print env 2 on success
 */
int builtin(char *cmd)
{
	if (_strncmp(cmd, "exit", 4) == 0)
	{
		return (0);
	}
	if (_strncmp(cmd, "env", 3) == 0)
	{
		printEnv();
		return (1);
	}
	return (-1);
}
/**
 * printEnv - print out environvironment
 */
void printEnv(void)
{
	char **env = environ;
	int i, j;

	for (i = 0; env[i]; i++)
	{
		j = 0;
		for (; env[i][j] != '\0'; j++)
			_printf("%s", env[i][j]);

		_printf("\n");
	}
}

/**
 * _getenv - get enviroment viariables
 * @name: input str
 * Return: ..
 */
char *_getenv(const char *name)
{
	int i, j;
	char **envp = environ;

	if (!name || !environ)
		return (NULL);

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; name[j] != '\0' && name[j] == envp[i][j]; j++)
		{
			/*compare characters until they differ or name[j] is null terminator*/
		}
		if (name[j] == '\0' && envp[i][j] == '=')
		{
			/* Found a matching environment variable*/
			char *value_start = &envp[i][j + 1];
			size_t value_length = strlen(value_start);

			char *value = malloc(value_length + 1);

			if (value)
			{
				strcpy(value, value_start);
				return (value);
			}
		}
	}

	return (NULL); /* No matching environment variable found*/
}
