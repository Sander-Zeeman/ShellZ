#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char *readString(bool properString, char firstChar, bool *isFinished, bool *error) {
    bool properFinish = false;
	int size = 0;
	char currChar;
	char *result = NULL;

	// Reinsert the first character, as mentioned in the header comment.
	if (!properString) {
		size++;
        result = (char*)realloc(result, size * sizeof(char));
		result[size - 1] = firstChar;
	}

    // Read until our exit condition, or '\n' (End of input line) is found.
	while ((currChar = getchar()) != '\n') {
		if (properString) {
			if (currChar == '"') {
                properFinish = true;
				break;
			}
		} else {
			if (currChar == ' ') {
				break;
			}
		}

		size++;
		result = realloc(result, size * sizeof(char));
		result[size - 1] = currChar;
	}

	// If we have a "proper" string, but did not find a closing ", the syntax must be incorrect.
	if (properString && !properFinish) {
        *error = true;
		invalidSyntaxError();
	}

	// Let the main tokenize function know whether the input line ended while reading a string.
	if (currChar == '\n') {
        *isFinished = true;
	}

	size++;
	result = realloc(result, size * sizeof(char));
	result[size - 1] = '\0';
	return result;
}

Token *tokenize(bool *error) {
    Token *startToken = NULL;
    Token *token = NULL;
    Token *prevToken = NULL;

    char currChar;
    bool finishedReading = false;

    // Continue reading until we have tokenized the entire input line.
    while (!finishedReading) {
		currChar = getchar();

		// An input line ends on a newline character.
		if (currChar == '\n') {
            finishedReading = true;
		    break;
		}

		// Ignore any spaces in our tokenizer, as they contribute nothing to our program after the tokenizer.
		if (currChar == ' ') {
		    continue;
		}

		token = malloc(sizeof(Token));
		token->content = NULL;
		token->next = NULL;

		char *str;

		// Set the current token's type, depending on which character is read.
		switch(currChar) {
		    case '<':
				token->type = IOIn;
				break;
		    case '>':
				token->type = IOOut;
				break;
		    case '&':
				token->type = Background;
				break;
		    case '|':
				token->type = Pipe;
				break;
		    // If a string is read, we need to use the content attribute of a token, which is left at NULL in all other cases.
		    // A "proper" string (surrounded by quotation marks)
		    case '"':
				token->type = String;
                token->content = readString(true, '\0', &finishedReading, error);
				break;
		    // If the token didn't match any other cases, it's a regular string.
			default:
                str = readString(false, currChar, &finishedReading, error);
				if (compare(str, "exit")) {
					free(str);
					token->type = Exit;
				} else {
					token->type = String;
					token->content = str;
				}
		}

		if (startToken == NULL) {
		    startToken = token;
		}

		if (prevToken != NULL) {
		    prevToken->next = token;
		}

		prevToken = token;
    }

    return startToken;
}
