#include "main.h"

/**
 * display_prompt - displays a prompt on the standard output
**/

void display_prompt(void)
{
write(STDOUT_FILENO, "$ ", 2);
fflush(stdout);
}

/**
 * tokenize_command - splits a command string into an array of arguments
 *
 * @command: the command string to tokenize
 * @args: the array of pointers to store the arguments
 *
**/

void tokenize_command(char *command, char *args[])
{
int i = 0;
char *token = strtok(command, " ");

while (token != NULL)
{
args[i++] = token;
token = strtok(NULL, " ");
}
args[i] = NULL;
}

/**
 * contains_slash - checks if a string contains a slash character
 *
 * @str: the string to check
 *
 * Return: 1 if the string contains a slash, or 0 otherwise
**/

int contains_slash(char *str)
{
while (*str)
{
if (*str == '/')
return (1);
str++;
}
return (0);
}

/**
 * execute_command - executes a command by creating a child process
 *
 * @command: the command string to execute
 * @line_number: the line number of the command in the program
 * @program_name: the name of the program that calls this function
 *
**/

void execute_command(char *command, int line_number, char *program_name)
{
    pid_t pid;
    char *args[MAX_COMMAND_LENGTH];
    tokenize_command(command, args);

    if (args[0] == NULL)
    {
        handle_invalid_command(program_name, line_number);
        return;
    }

    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        _exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        exe_external_command(args, program_name, line_number);
        _exit(EXIT_SUCCESS);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}

/**
 * print_environment_variables - prints all the environment variables
**/

void print_environment_variables(void)
{
char **env;

for (env = environ; *env != NULL; env++)
{
write(STDOUT_FILENO, *env, _strlen(*env));
write(STDOUT_FILENO, "\n", 1);
}
}
