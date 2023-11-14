#ifndef MYHEADERS_H
#define MYHEADERS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

extern char **environ;




int _putchar(char c);
void display_prompt(void);
void tokenize_command(char *command, char *args[]);
void execute_command(char *command, int line_number, char *program_name);
void print_environment_variables(void);
int _strlen(char *s);
char *_strdup(char *str);
int _strcmp(char *s1, char *s2);
char *itoa(int val, int base);
char *_strcpy(char *dest, char *src);
void exe_external_command(char *args[], char *program_name, int line_number);
int contains_slash(char *str);
void handle_invalid_command(char *program_name, int line_number);
void handle_com_not_found(char *program_name, int line_number, char *command);



#endif
