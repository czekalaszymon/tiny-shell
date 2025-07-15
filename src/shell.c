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

int builtin_cd(char** argv) {
    if (argv[1] == NULL) {
        fprintf(stderr, "cd: missing argument\n");
        return 1;
    }
    if (chdir(argv[1]) != 0) {
        perror("cd");
        return 1;
    }
    return 0;
}

int handle_builtin(char** argv) {
    struct builtin_command builtins[] = {
        { "cd", builtin_cd },
    };
    
    // Number of built-ins in the list
    int num_builtins = sizeof(builtins) / sizeof(builtins[0]);

    for (int i = 0; i < num_builtins; ++i) {
        if (strcmp(argv[0], builtins[i].name) == 0) {
            return builtins[i].func(argv);
        }
    }

    return -1;  // not a builtin
}
