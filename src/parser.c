#include "parser.h"

// Note how a reference to a reference to a pointer is used throughout the parser.
// This is done so all functions modify the same token pointer, which is useful, as every token should only be evaluated once.
// NOTE: FINISH COMMENTING
CommandPart parseCommandPart(Token **token, bool *error) {
    CommandPart part;
    part.name = NULL;
    part.options = NULL;
    part.optionCount = 0;

    if (*token != NULL && (*token)->type == String) {
		part.name = copy((*token)->content);
		*token = (*token)->next;
    } else {
		*error = TRUE;
		invalidSyntaxError();
    }

    while (*token != NULL && (*token)->type == String) {
		part.optionCount++;
		part.options = realloc(part.options, part.optionCount * sizeof(char*));
		part.options[part.optionCount - 1] = copy((*token)->content);

		*token = (*token)->next;
    }

    return part;
}

CommandList parseCommandList(Token **token, bool *error) {
    CommandList list;
    list.parts = malloc(sizeof(CommandPart));
    list.partsCount = 1;
    list.parts[0] = parseCommandPart(token, error);

    while (*token != NULL && (*token)->type == Pipe) {
		*token = (*token)->next;

		list.partsCount++;
		list.parts = realloc(list.parts, list.partsCount * sizeof(CommandPart));
		list.parts[list.partsCount - 1] = parseCommandPart(token, error);
    }

    return list;
}

void parseIOSingle(Token **token, TokenType type, IORedirect *io, bool *error) {
    if (*token != NULL && (*token)->type == type) {
		*token = (*token)->next;
		if (*token != NULL && (*token)->type == String) {
		    if (type == IOIn) {
				io->inFilename = copy((*token)->content);
				*token = (*token)->next;
				parseIOSingle(token, IOOut, io, error);
		    } else {
				io->outFilename = copy((*token)->content);
				*token = (*token)->next;
				parseIOSingle(token, IOIn, io, error);
		    }
		} else {
			*error = TRUE;
		    invalidSyntaxError();
		}
    }
}

IORedirect parseIORedirect(Token **token, bool *error) {
    IORedirect io;
    io.inFilename = NULL;
    io.outFilename = NULL;

    if (*token != NULL && (*token)->type == IOIn) {
		parseIOSingle(token, IOIn, &io, error);
    } else {
		parseIOSingle(token, IOOut, &io, error);
    }
    return io;
}

Command parseCommand(Token **token, bool *error) {
    Command command;
	if ((*token)->type == Exit) {
		command.exit = TRUE;
		*token = (*token)->next;
	} else {
	    command.command = parseCommandList(token, error);
	    command.io = parseIORedirect(token, error);
		command.exit = FALSE;

	    if (compare(command.io.inFilename, command.io.outFilename)) {
			*error = TRUE;
			sameNameError();
	    }

		if (*token && (*token)->type == Background) {
			command.isBackground = TRUE;
			*token = (*token)->next;
		} else {
			command.isBackground = FALSE;
		}
	}
    return command;
}

Input parseInput(Token **token, bool *error) {
    Input input;
    input.commands = NULL;
    input.commandCount = 0;

    while (*token != NULL) {
		input.commandCount++;
		input.commands = realloc(input.commands, input.commandCount * sizeof(Command));
		input.commands[input.commandCount - 1] = parseCommand(token, error);
		if (*token == NULL) {
		    break;
		}
    }

    return input;
}
