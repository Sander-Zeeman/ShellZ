#include "errors.h"
#include "utilities.h"
#include "structs.h"
#include "memory.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

void runInput(Input input, int *active, int **processes, int *processCount);
