/*
 * lexer.c/h lexes/tokenizes our input, so the parser can interpret it more easily,.
 * as well as detect errors far more easily.
 */

#include "structs.h"
#include "errors.h"
#include "utilities.h"

#include <stdio.h>

char *readString(bool isProperString, char firstChar, bool *isFinished, bool *error);

Token *tokenize(bool *error);
