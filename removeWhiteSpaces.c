#include "shell.h"

/**
 * _isspace - defines white space
 * @c: input character
 * Return: true if the input str is a white space
 * else otherwise
*/
bool _isspace(char c)
{
	/* Define your criteria for white space characters here*/
	return (c == ' ' || c == '\t' || c == '\n');
}

/**
 * removeLeadingTrailingWhitespace - remove all white spaces
 * @str: input string
*/
void removeLeadingTrailingWhitespace(char *str)
{
	int len = strlen(str), newLen;
	int leadingSpaces = 0, trailingSpaces = 0;

	if (!str || *str == '\0')
		return;

	/* Find the number of leading spaces*/
	for (; _isspace(str[leadingSpaces]); leadingSpaces++)

	/*If the entire string is composed of spaces, make it an empty string*/
	if (leadingSpaces == len)
	{
		str[0] = '\0';
		return;
	}

	/* Find the number of trailing spaces*/
	for (; _isspace(str[len - 1 - trailingSpaces]); trailingSpaces++)

	/* Calculate the new length of the string exclude leading, trailing spaces)*/
	newLen = len - leadingSpaces - trailingSpaces;

	/* Shift the remaining characters to the beginning of the string*/
	memmove(str, str + leadingSpaces, newLen);

	/* Add null terminator to the end of the new string*/
	str[newLen] = '\0';
}
