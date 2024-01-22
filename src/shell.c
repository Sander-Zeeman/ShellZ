#include "shell.h"

#include <stdio.h>

char **fixOptions(char *name, char **options, int count) {
	char **newOptions = malloc((count + 2) * sizeof(char*));
    newOptions[count + 1] = NULL;
	for (int i = count - 1; i >= 0; i--) {
		newOptions[i + 1] = copy(options[i]);
	}
	newOptions[0] = copy(name);
	return newOptions;
}

void redirectStandardFile(char *newFile, int descriptor, bool input) {
    int fd = open(newFile, input ? O_RDONLY : O_WRONLY);
    if (fd == -1) {
	FILE *fp;
	fp = fopen(newFile, "w");
	fclose(fp);
	fd = open(newFile, input ? O_RDONLY : O_WRONLY);
    }
    dup2(fd, descriptor);
    close(fd);
}

void runPart(CommandPart part) {
    char *name = part.name;
    char **options = part.options;
    int count = part.optionCount;

    options = fixOptions(name, options, count);

    execvp(name, options);
	notFoundError();
	exit(1);
}

void runCommand(Command command) {
    CommandList list = command.command;
    IORedirect io = command.io;

    if (io.inFilename) {
	redirectStandardFile(io.inFilename, STDIN_FILENO, TRUE);
    }

    int fd[2];
    int pid;
    for (int i = 0; i < list.partsCount - 1; i++) {
	if (pipe(fd) == -1) {
	    perror("pipe");
	    exit(1);
	}

	pid = fork();
	if (pid == 0) {
	    dup2(fd[1], STDOUT_FILENO);
	    runPart(list.parts[i]);
	    exit(1);
	}

	dup2(fd[0], STDIN_FILENO);

	close(fd[0]);
	close(fd[1]);
    }

    if (io.outFilename) {
	redirectStandardFile(io.outFilename, STDOUT_FILENO, FALSE);
    }

    runPart(list.parts[list.partsCount - 1]);
}


void runInput(Input input, int *active, int **processes, int *processCount) {
	pid_t pid;

    for (int i = 0; i < input.commandCount; i++) {
		(*active)++;
		pid = fork();

		if (pid == 0) {
		    runCommand(input.commands[i]);
		    exit(1);
		} else {
			if (!input.commands[i].isBackground) {
				waitpid(pid, NULL, 0);
			} else {
				(*processCount)++;
				*processes = realloc(*processes, *processCount * sizeof(int));
				(*processes)[*processCount - 1] = pid;
			}
		}
   }
}
