/*
 * structs.h contains some definitions, structs and typedefs that are commonly used by many files.
 */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <sys/types.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int bool;

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
	// Would make a new struct for custom commands, however, as I likely don't have time, a boolean will do.
	bool exit;
    CommandList command;
    IORedirect io;
	bool isBackground;
} Command;

typedef struct Input {
    Command *commands;
    int commandCount;
} Input;


typedef enum TokenType {
    String,
    IOIn,
    IOOut,
    Background,
    Pipe,
	Exit
} TokenType;

typedef struct Token {
    char *content;
    TokenType type;
    struct Token *next;
} Token;

#endif
