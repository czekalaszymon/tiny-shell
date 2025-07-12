#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "shell.h"

void parse_input(char* input, char** argv)
{
	char* token;
	int i = 0;

	token = strtok(input, " ");
	while (token != NULL && i < SHELL_MAX_ARGS - 1) {
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
}

void run_command(char** argv)
{
	pid_t pid = fork();
	if (pid == 0) {
		// Child process
		execvp(argv[0], argv);
		perror("exec failed");
		exit(1);
	} else if (pid > 0) {
		// Parent process
		waitpid(pid, NULL, 0);
	}
	else {
		perror("fork failed");
	}
}
