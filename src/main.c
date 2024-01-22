#include "main.h"
#include "utilities.h"
#include <stdio.h>

Input readCommand(int *error) {
    Token *token = tokenize(error);
    Token *copy;
    copy = token;
    Input input = parseInput(&token, error);
    freeTokens(copy);
    return input;
}

int active = 0;

void handle_sigchld(int sig) {
	active--;
}

int main() {
	bool error = FALSE;
	bool finished = FALSE;

	int *processes;
	processes = NULL;
	int processCount = 0;

    Input currentInput;
	signal(SIGCHLD, handle_sigchld);
	setbuf(stdout, NULL);

	while (!finished) {
		currentInput = readCommand(&error);

		if (error) {
			freeInput(&currentInput);
			error = FALSE;
			continue;
		}

		if (currentInput.commandCount == 1 && currentInput.commands[0].exit) {
			if (active == 0) {
				finished = TRUE;
			} else {
				backgroundError();
			}
		} else {
			runInput(currentInput, &active, &processes, &processCount);
		}

		freeInput(&currentInput);
	}

	//All processes have exited, however, the children are still in the process table.
	for (int i = 0; i < processCount; i++) {
		waitpid(processes[i], NULL, 0);
	}

	if (processCount > 0) {
		free(processes);
	}

    return 0;
}
