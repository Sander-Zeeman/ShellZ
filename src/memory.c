#include "memory.h"

#include <stdio.h>

void freeTokens(Token *token) {
    if (token != NULL) {
        freeTokens(token->next);
        if (token->content) {
        	free(token->content);
        }
        free(token);
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
