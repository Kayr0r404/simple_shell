#include "shell.h"

/**
 * path_ls_bin - breaks strings and excute them
 * @cmd: command from the user
 *
 * Return: 0 on success 1 if exec function returns 1
 */
int path_ls_bin(char *cmd)
{
	int argc = 0, status = 0;
	char **argv = NULL, *token = NULL;

	argv = malloc(sizeof(char *) * SIZE);

	token = _strtok(cmd, LINE_DELIM);
	argv[0] = token;
	while (token)
	{
		argc++;
		token = _strtok(NULL, LINE_DELIM);
		argv[argc] = token;
	}
	argv[argc] = NULL;
	status = exec(argv, NULL);
	free(argv);

	return (status);
}

/**
 * path_ls - breaks strings and excute them
 * @cmd: command from the user
 *
 * Return: 0 on success 1 if exec function returns 1
 */
int path_ls(char *cmd)
{
	int argc = 0, status = 0;
	char **argv2 = NULL, *token = NULL, *cmd2 = NULL;

	cmd2 = malloc(sizeof(char *) * SIZE);

	cmd2 = _strcpy(cmd2, "/bin/");
	cmd2 = _strcat(cmd2, cmd);

	argv2 = malloc(sizeof(char *) * SIZE);

	token = _strtok(cmd2, LINE_DELIM);
	argv2[0] = token;
	while (token)
	{
		argc++;
		token = _strtok(NULL, LINE_DELIM);
		argv2[argc] = token;
	}
	argv2[argc] = NULL;

	status = exec(argv2, NULL);
	free(cmd2);
	free(argv2);
	return (status);
}

/**
* findCommandInPath - find the path of the command
* @command: command to search for
* Return: full absolute path
*/

char *findCommandInPath(const char *command)
{
	char *path = _getenv("PATH"), *directory, *pathCopy;

	if (path == NULL)
	{
		_printf("Error: PATH environment variable not found.\n");
		return (NULL);
	}

	pathCopy = _strdup(path);
	if (pathCopy == NULL)
	{
		_printf("Error: Memory allocation failed.\n");
		return (NULL);
	}

	directory = _strtok(pathCopy, ":");
	while (directory != NULL)
	{
		int commandLen = _strlen(directory) + _strlen(command) + 2;
		char *fullCommandPath = (char *)malloc(commandLen * sizeof(char));

		if (fullCommandPath == NULL)
		{
			_printf("Error: Memory allocation failed.\n");
			free(pathCopy);
			return (NULL);
		}

		snprintf(fullCommandPath, commandLen, "%s/%s", directory, command);

		if (access(fullCommandPath, F_OK) == 0)
			return (_strdup(_strcat(directory, "/")));

		free(fullCommandPath);
		directory = _strtok(NULL, ":");
	}

	free(pathCopy);
	return (NULL);
}

/**
 * isAbsolutePath - Function to check if the command is an absolute path
 * @cmd: input string
 * Return: true if command is an absolute path, false otherwise
 */
bool isAbsolutePath(const char *cmd)
{
	if (cmd == NULL || _strlen(cmd) == 0)
		return (false);

	/* Check if it starts with a forward slash or Windows-style drive letter*/
	return (cmd[0] == '/' ||
	(_strlen(cmd) >= 3 && cmd[1] == ':' && cmd[2] == '/'));
}

/**
 * extractCommandFromPath - extract command from absolute path
 * @fullPath: Absolute Path
 * Return: Extracted command
*/
char *extractCommandFromPath(const char *fullPath)
{
	char *command = strrchr(fullPath, '/'); /* Find the last occurrence of '/'*/

	if (!command)
	{
		/* No '/' found in the path, return a copy of the fullPath*/
		return (_strdup(fullPath));
	}

	/* Increment the pointer to skip the '/'*/
	/* Allocate memory for the command name*/
	return (_strdup(++command));
}
