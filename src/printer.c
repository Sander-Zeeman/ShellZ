#include "printer.h"

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


void printTokenType(TokenType type) {
    switch(type) {
	case String:
	    printf("String");
	    break;
	case IOIn:
	    printf("IOIn");
	    break;
	case IOOut:
	    printf("IOOut");
	    break;
	case Background:
	    printf("Background");
	    break;
	case Pipe:
	    printf("Pipe");
	    break;
	case Exit:
		printf("Exit");
		break;
	default:
	    printf("Unknown Token Type!");
	    break;
    }

    putchar('\n');
}

void printTokens(Token *token) {
    while (token != NULL) {
	printf("Token Type: ");
	printTokenType(token->type);
	if (token->type == String) {
	    printf("Content: %s\n", token->content);
	}

	token = token->next;
    }
    putchar('\n');
}
