#include <stdio.h>
#include <string.h>

#include "shell.h"

int main()
{
	char buff[SHELL_MAX_INPUT];
	char* argv[SHELL_MAX_ARGS];

	while (1) {
		printf("> ");
		if (fgets(buff, sizeof(buff), stdin) == NULL)
			break;

		// Remove trailing newline
		buff[strcspn(buff, "\n")] = 0;

		parse_input(buff, argv);

		if (argv[0] == NULL)
			continue;

		if (strcmp(argv[0], "exit") == 0)
			break;

		if (handle_builtin(argv) == -1) {
			run_command(argv);
		}
	}

	return 0;
}
