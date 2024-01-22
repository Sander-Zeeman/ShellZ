/*
 * printer.c/h contains functions to print our tokens and data structures.
 * only used in debugging, can be deleted when handing in the code.
 */

#include "structs.h"

#include <stdio.h>

void printTabs(int depth);

void printCommandPart(CommandPart part, int depth);

void printCommandList(CommandList list, int depth);

void printIORedirect(IORedirect io, int depth);

void printCommand(Command comm, int depth);

void printInput(Input inp, int depth);

void printTokenType(TokenType type);

void printTokens(Token *token);
