#include "main.h"

/**
 * handle_invalid_command - prints an error message
 *
 * @program_name: the name of the program
 * @line_number: the line number where the error occurred
 *
 */

void handle_invalid_command(char *program_name, int line_number)
{
char *line_number_str = itoa(line_number, 10);

write(STDERR_FILENO, program_name, _strlen(program_name));
write(STDERR_FILENO, ": ", 2);
write(STDERR_FILENO, line_number_str, _strlen(line_number_str));
write(STDERR_FILENO, ": Invalid command\n", 18);
_exit(EXIT_FAILURE);
}

/**
 * handle_com_not_found - prints an error message
 *
 * @program_name: the name of the program
 * @line_number: the line number where the error occurred
 * @command: the command that was not found
 *
 **/

void handle_com_not_found(char *program_name, int line_number, char *command)
{
char *line_number_str = itoa(line_number, 10);

write(STDERR_FILENO, program_name, _strlen(program_name));
write(STDERR_FILENO, ": ", 2);
write(STDERR_FILENO, line_number_str, _strlen(line_number_str));
write(STDERR_FILENO, ": ", 2);
write(STDERR_FILENO, command, _strlen(command));
write(STDERR_FILENO, ": not found\n", 12);
_exit(EXIT_FAILURE);
}

/**
 * exe_external_command - executes an external command
 *
 * @args: a NULL-terminated array of arguments
 * @program_name: the name of the program
 * @line_number: the line number where the command was read
 *
 **/


void exe_external_command(char *args[], char *program_name, int line_number)
{
char *envp[] = {NULL};
char exec_path[MAX_COMMAND_LENGTH];

if (args[0] == NULL)
handle_invalid_command(program_name, line_number);

if (contains_slash(args[0]))
{
execve(args[0], args, envp);
}
else
{
char *path = getenv("PATH");
char *path_copy = _strdup(path);
char *dir = strtok(path_copy, ":");

while (dir != NULL)
{
int dir_len = _strlen(dir);
int arg_len = _strlen(args[0]);

if (dir_len + arg_len + 2 <= MAX_COMMAND_LENGTH)
{
_strcpy(exec_path, dir);
exec_path[dir_len] = '/';
_strcpy(exec_path + dir_len + 1, args[0]);
if (access(exec_path, X_OK) == 0)
{
execve(exec_path, args, envp);
break;
}
}
dir = strtok(NULL, ":");
}
free(path_copy);
handle_com_not_found(program_name, line_number, args[0]);
}
}
