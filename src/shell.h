#ifndef SHELL_H
#define SHELL_H

#define SHELL_MAX_INPUT 256
#define SHELL_MAX_ARGS 16

void parse_input(char* input, char** argv);
void run_command(char** argv);

struct builtin_command {
	const char* name;
	int (*func)(char** argv);
};

int handle_builtin(char** argv);

#endif
