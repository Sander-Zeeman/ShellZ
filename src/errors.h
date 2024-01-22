/*
 * errors.c/h contains all error messages that our shell can produce, so they can all be modified for the entire code, should this be necessary.
 * Currently handles the following errors:
 * - Invalid Syntax
 * - Same Name
 */

#ifndef ERRORS_H
#define ERRORS_h

#include <stdio.h>

void invalidSyntaxError();

void sameNameError();

void backgroundError();

void notFoundError();

#endif
