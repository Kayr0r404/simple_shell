#include "shell.h"
/**
 * _strndup - sup n chars of str
 * @str: input str
 * @n: number chars to be dup
 * Return: duplicated str
*/

char *_strndup(const char *str, size_t n)
{
	char *new_str;
	size_t i, length = 0;

	while (length < n && str[length] != '\0')
	{
		/* actual length of the string within the specified limit*/
		length++;
	}

	/* Allocate memory for the new string (plus one for the null terminator)*/
	new_str = malloc(length + 1);
	if (new_str != NULL)
	{
		for (i = 0; i < length; i++)
		{
			/* Copy each character from the original string to the new string*/
			new_str[i] = str[i];
		}

		/* Add the null terminator at the end of the new string*/
		new_str[length] = '\0';
	}

	return (new_str);
}

/**
 * _cd - implementation of change working directory
 * @argc: num of arguments/ num of commands
 * @argv: array of strings/ arrayy of commands
 * parameters of cd, if argv is NULL, then change the
 * working directory to hone direcyory.
 * handle parameters ..(parent dir) and -(previous dir)
 * Return: path to destination dir
 */

void _cd(char *cmd)
{
	char *home_dir = _getenv("HOME"), *old_pwd = _getenv("OLDPWD"), *new_pwd = NULL;
	char **argv = malloc(sizeof(char *) * SIZE);

	argv = tok(cmd);

	if ( _strncmp(argv[1], "~", 1) == 0)
	{
		/* If no argument// arg = ~ is given, change to the HOME directory*/
		if (chdir(home_dir) != 0)
			perror("cd");
	}
	else
	{
		char *arg = argv[1];

		if (_strncmp(arg, "-", 1) == 0)
		{
			/* If argument is '-', change to the previous directory*/
			if (old_pwd == NULL)
				_printf("cd: OLDPWD not set\n");
			else
			{
				if (chdir(old_pwd) != 0)
					perror("cd");
			}
		}
		if(is_directory(arg))
		{
			if (chdir(arg) != 0)
				perror("No such file or directory");
		}
	}

	/* Update the PWD and OLDPWD environment variables*/
	new_pwd = getcwd(NULL, 0);
	if (new_pwd != NULL)
		setenv("OLDPWD", _getenv("PWD"), 1), setenv("PWD", new_pwd, 1), free(new_pwd);
	else
		perror("cd");
	free(argv);
}

/**
 * is_directory - checks if passed pararameter is a dir
 * @path: input path/ dir
 * Return: false if not a dir else true
*/
bool is_directory(const char *path)
{
	struct stat st;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (true);
	}

	return (false);
}
