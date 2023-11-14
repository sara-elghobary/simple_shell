#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define MAX_COMMAND_LENGTH 1024



/**
 * main - the entry point of the program
 *
 * @argc: the number of arguments passed to the program
 * @argv: the array of pointers to the arguments
 *
 * Return: 0 on successful exit, or other values on failure
 **/
int main(int argc, char *argv[])
{
process_arguments(argc, argv);

return (0);
}

void process_arguments(int argc, char *argv[])
{
if (argc > 1)
{
for (int i = 1; i < argc; i++)
{
process_file(argv[i], argv[0]);
}
}
else
process_input_interactive();

}

void process_file(char *filename, char *program_name)
{
int file_fd = open(filename, O_RDONLY);
if (file_fd == -1)
{
perror("open");
exit(EXIT_FAILURE);
}

char *command = NULL;
size_t len = 0;
ssize_t nread;
int line_number = 0;

while ((nread = getline(&command, &len, stdin)) != -1)
{
if (nread > 0 && command[nread - 1] == '\n')
command[nread - 1] = '\0';

execute_command(command, line_number, program_name);
line_number++;
}

free(command);
close(file_fd);
}

void process_input_interactive(void)
{
char *command = NULL;
size_t len = 0;
ssize_t nread;
int line_number = 0;

while (1)
{
display_prompt();
nread = getline(&command, &len, stdin);

if (nread == -1)
{
write(STDOUT_FILENO, "\n", 1);
break;
}

for (int i = 0; i < nread; i++)
{
if (command[i] == '\n')
{
command[i] = '\0';
break;
}
}

line_number++;
if (_strcmp(command, "exit") == 0)
{
break;
}
else if (_strcmp(command, "env") == 0)
{
print_environment_variables();
}
else
execute_command(command, line_number, "shell");

}

free(command);
}
