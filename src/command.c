#include "command.h"

#include <stdio.h>
#include <stdlib.h>

void printTabs(int depth) {
    for (int i = 0; i < depth; i++) {
        putchar('\t');
    }
}

void printCommandPart(CommandPart part, int depth) {
    printTabs(depth);
    printf("Name: %s\n", part.name);
    printTabs(depth);
    printf("Number of options: %d\n", part.optionCount);
    for (int i = 0; i < part.optionCount; i++) {
        printTabs(depth);
        printf("Option: %s\n", part.options[i]);
    }
    printf("\n");
}

void printCommandList(CommandList list, int depth) {
    printTabs(depth);
    printf("Number of parts: %d\n", list.partsCount);
    for (int i = 0; i < list.partsCount; i++) {
        printCommandPart(list.parts[i], depth + 1);
    }
    printf("\n");
}

void printIORedirect(IORedirect io, int depth) {
    if (io.inFilename) {
        printTabs(depth);
        printf("In: %s\n", io.inFilename);
    }
    if (io.outFilename) {
        printTabs(depth);
        printf("Out: %s\n", io.outFilename);
    }
    printf("\n");
}

void printCommand(Command comm, int depth) {
    printTabs(depth);
    printf("Command List:\n");
    printCommandList(comm.command, depth + 1);
    printTabs(depth);
    printf("IO Redirect:\n");
    printIORedirect(comm.io, depth + 1);
}

void printInput(Input inp, int depth) {
    printTabs(depth);
    printf("Number of commands: %d\n", inp.commandCount);
    for (int i = 0; i < inp.commandCount; i++) {
        printTabs(depth);
        printCommand(inp.commands[i], depth + 1);
    }
}

void freeCommandPart(CommandPart part) {
    if (part.name) {
        free(part.name);
    }

    if (part.options) {
        for (int i = 0; i < part.optionCount; i++) {
            free(part.options[i]);
        }
        free(part.options);
    }
}

void freeCommandList(CommandList list) {
    if (list.parts) {
        for (int i = 0; i < list.partsCount; i++) {
            freeCommandPart(list.parts[i]);
        }
        free(list.parts);
    }
}

void freeIORedirect(IORedirect io) {
    if (io.inFilename) {
        free(io.inFilename);
    }

    if (io.outFilename) {
        free(io.outFilename);
    }
}

void freeCommands(Command *commands, int size) {
    if (commands) {
        for (int i = 0; i < size; i++) {
            if (!commands[i].exit) {
                freeCommandList(commands[i].command);
                freeIORedirect(commands[i].io);
            }
        }
        free(commands);
    }
}

void freeInput(Input *input) {
    freeCommands(input->commands, input->commandCount);
}
