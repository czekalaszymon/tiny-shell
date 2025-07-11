#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	char buff[256];
	char* argv[16];
	char* token;

	while (1) {
		printf("> ");
		if (fgets(buff, sizeof(buff), stdin) == NULL) break;

		// Remove trailing newline from fgets
		buff[strcspn(buff, "\n")] = 0;

		int i = 0;
		token = strtok(buff, " ");
		while (token != NULL && i < 15) {
			argv[i++] = token;
			token = strtok(NULL, " ");
		}
		argv[i] = NULL;

		if (argv[0] == NULL) continue;

		if (strcmp(argv[0], "exit") == 0) break;

		// Fork and exec
		pid_t pid = fork();
		if (pid == 0) {
			// Child process
			execvp(argv[0], argv);
			perror("exec failed");
			exit(1);
		} else if (pid > 0)
			// Parent process
			waitpid(pid, NULL, 0);
		else
			perror("fork failed");
	}

	return 0;
}
