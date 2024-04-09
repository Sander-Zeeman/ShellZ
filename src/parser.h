#pragma once

#include "command.h"
#include "token.h"

#include <stdbool.h>

Input parseInput(Token **token, bool *error);
