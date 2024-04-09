#pragma once

#include "token.h"

#include <stdbool.h>

typedef struct CommandPart {
    char *name;
    char **options;
    int optionCount;
} CommandPart;

typedef struct CommandList {
    CommandPart *parts;
    int partsCount;
} CommandList;

typedef struct IORedirect {
    char *inFilename;
    char *outFilename;
} IORedirect;

typedef struct Command {
    bool exit;
    CommandList command;
    IORedirect io;
    bool isBackground;
} Command;

typedef struct Input {
    Command *commands;
    int commandCount;
} Input;

void printTabs(int depth);
void printCommandPart(CommandPart part, int depth);
void printCommandList(CommandList list, int depth);
void printIORedirect(IORedirect io, int depth);
void printCommand(Command comm, int depth);
void printInput(Input inp, int depth);

void freeTokens(Token *token);
void freeCommandPart(CommandPart part);
void freeCommandList(CommandList list);
void freeIORedirect(IORedirect io);
void freeCommands(Command *commands, int size);
void freeInput(Input *input);
