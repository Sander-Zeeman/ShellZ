#include "command.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

void runInput(Input input, int *active, int **processes, int *processCount);
