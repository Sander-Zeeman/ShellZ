#include "errors.h"

#include <stdio.h>

void invalidSyntaxError() {
    printf("Error: invalid syntax!\n");
}

void sameNameError() {
    printf("Error: input and output files cannot be equal!\n");
}

void backgroundError() {
    printf("Error: there are still background processes running!\n");
}

void notFoundError() {
    printf("Error: command not found!\n");
}
