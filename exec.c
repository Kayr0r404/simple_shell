#include "shell.h"

/**
 * exec - executing function
 * @argument: command argument
 * @argv: argument vector
 *
 * Return: 0 on success 1 if pid is 1 if pid is different from 0
 */
int exec(char **argument, char **argv)
{
	pid_t pid;
	int status;
	char *comm = argument[0];

		pid = fork();
		if (pid == 0)
		{
			if (execve(comm, argument, environ) == -1)
			{
				error(argv[0], comm);
				exit(127);
			}
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			return (errno);
		}

	return (0);
}

/**
 * executeCmd - breaks strings and excute them
 * @cmd: command from the user
 * Return: 0 on success 1 if exec function returns 1
 */
int executeCmd(char *cmd)
{
	int status = 0;
	char **argv2 = NULL, *cmd2 = NULL, *path;
	char *tmpCmd = extractCommandFromPath(_strdup(cmd));

	if (isAbsolutePath(cmd))
		cmd = extractCommandFromPath(cmd);

	cmd2 = malloc(sizeof(char *) * SIZE);
	if (_strncmp(cmd, "cd", 2) == 0)
	{
			_cd(cmd);
		return (0);
	}
	else
	{
		path = findCommandInPath(_strtok(cmd, " "));
		if (!path)
		{
			_printf("%s: command not found\n", cmd);
			return (-1);
		}
	}
	cmd2 = _strcat(path, tmpCmd);

	argv2 = malloc(sizeof(char *) * SIZE);
	argv2  = tok(cmd2);
	status = exec(argv2, NULL);
	free(cmd2), free(argv2);

	return (status);
}

/**
 * is_cmd - determines if a file is an executable command
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(char *path)
{
	struct stat st;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * tok - tokenize string and put them in an array
 * @str: input string to be tokenized
 * Return: an array of strings
*/
char **tok(char *str)
{
	char *token, **argv;
	int argc = 0;

	argv = malloc(sizeof(char *) * SIZE);
	token = _strtok(str, LINE_DELIM);
	argv[0] = token;
	while (token)
	{
		argc++;
		token = _strtok(NULL, LINE_DELIM);
		argv[argc] = token;
	}
	argv[argc] = NULL;
	return (argv);
}
