/*
 * parser.c/h is responsible for parsing a parsing a token list and detecting any syntax errors in the process.
 */

#include "structs.h"
#include "utilities.h"
#include "errors.h"

CommandPart parseCommandPart(Token **token, bool *error);

CommandList parseCommandList(Token **token, bool *error);

void parseIOSingle(Token **token, TokenType type, IORedirect *io, bool *error);

IORedirect parseIORedirect(Token **token, bool *error);

Command parseCommand(Token **token, bool *error);

Input parseInput(Token **token, bool *error);
