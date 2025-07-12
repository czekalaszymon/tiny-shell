#ifndef SHELL_H
#define SHELL_H

#define SHELL_MAX_INPUT 256
#define SHELL_MAX_ARGS 16

void parse_input(char* input, char** argv);
void run_command(char** argv);

#endif
