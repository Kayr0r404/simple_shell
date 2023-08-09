#ifndef SHELL_H
#define SHELL_H
/************************************************
 *                                              *
 *              LIBRARIES                       *
 *                                              *
************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>
#include <limits.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <linux/types.h>
/************************************************
 *                                              *
 *              MACROS                       *
 *                                              *
************************************************/
#define LINE_DELIM " \t\n"
#define SIZE 1024
extern char **environ;

/************************************************
 *                                              *
 *              STRUCTUIRES                       *
 *                                              *
************************************************/
/**
 * struct linkedLists_node - Linked List
 * @next: next node
 * @id: int idedntifying a node
 * @var: environ variable
 * @key: environ varible value
*/
typedef struct linkedLists_node
{

	unsigned int id;
	const char *var;
	char *key;
	struct linkedLists_node *next;
} list_t;

/************************************************
 *                                              *
 *              PROTOTYPES                       *
 *                                              *
************************************************/
void remove_space(char *str);
void remove_string(char *str);
int start_w(const char *str, const char *sub, int index);

void error(char *name, char *cmd_name);

int builtin(char *cmd);
int exec(char **argument, char **av);
int executeCmd(char *cmd);
int path_ls(char *cmd2);
int path_ls_bin(char *cmd);
void print_env(void);

/*me*/
bool substringStartsAt(const char *str, const char *substr, int index);
void remove_substring(char *str, const char *substr);
void _error(char *name, char *cmd_name);
int _strlen(const char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(const char *str1, const char *str2);
int max(int a, int b);
char *_strchr(const char *str, int c);
char *_strcat(char *dest, char *src);
char *_strdup(const char *str);
int _strncmp(const char *str1, const char *str2, size_t n);
char *_strtok(char *str, const char *delim);
ssize_t _getline(char **lineptr, size_t *n, int fd);
/*Output Functions*/
void _putchar(char c);
void _putstr(const char *str);
void _printf(const char *format, ...);
/*PATH Functions*/
char *findCommandInPath(const char *command);
int is_cmd(char *path);
void printEnv(void);
char *_getenv(const char *name);
void removeLeadingTrailingWhitespace(char *str);
bool _isspace(char c);
bool is_directory(const char *path);
bool isAbsolutePath(const char *cmd);
char *extractCommandFromPath(const char *fullPath);
char **tok(char *str);

void _cd(char *cmd);
#endif
