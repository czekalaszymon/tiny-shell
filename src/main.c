#include <stdio.h>
#include <string.h>

#include "shell.h"

#define MAX_INPUT 256
#define MAX_ARGS

int main()
{
	char buff[MAX_INPUT];
	char* argv[MAX_ARGS];

	while (1) {
		printf("> ");
		if (fgets(buff, sizeof(buff), stdin) == NULL) break;

		// Remove trailing newline
		buff[strcspn(buff, "\n")] = 0;

		parse_input(buff, argv);

		if (argv[0] == NULL) continue;

		if (strcmp(argv[0], "exit") == 0) break;

		run_command(argv);
	}

	return 0;
}
