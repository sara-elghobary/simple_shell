#include "main.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024



/**
 * main - the entry point of the program
 *
 * @argc: the number of arguments passed to the program
 * @argv: the array of pointers to the arguments
 *
 * Return: 0 on successful exit, or other values on failure
 **/


int main(int argc, char *argv[]) {
    char *command = NULL;
    size_t len = 0;
    ssize_t nread;
    int line_number = 0;
    int i;

    int is_interactive = isatty(STDIN_FILENO);

    if (argc > 1) {
        for (i = 1; i < argc; i++) {
            int file_fd = open(argv[i], O_RDONLY);
            if (file_fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }

            while ((nread = read(file_fd, command, MAX_COMMAND_LENGTH)) != -1) {
                if (nread > 0) {
                    if (command[nread - 1] == '\n') {
                        command[nread - 1] = '\0';
                    }
                }
                if (is_interactive) {
                    display_prompt();
                }
                execute_command(command, line_number, argv[0]);
                line_number++;
            }

            close(file_fd);
        }
    } else {
        while (1) {
            if (is_interactive) {
                display_prompt();
            }
            nread = getline(&command, &len, stdin);
            if (nread == -1) {
                if (is_interactive) {
                    write(STDOUT_FILENO, "\n", 1);
                }
                break;
            }
            if (command != NULL) {
                for (i = 0; i < nread; i++) {
                    if (command[i] == '\n') {
                        command[i] = '\0';
                        break;
                    }
                }
            }
            line_number++;
            if (_strcmp(command, "exit") == 0)
                break;
            else if (_strcmp(command, "env") == 0)
                print_environment_variables();
            else
                execute_command(command, line_number, argv[0]);
        }
    }

    free(command);

    return 0;
}
