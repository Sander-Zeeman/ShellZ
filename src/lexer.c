#include "lexer.h"

/*
 * This functions reads from the input file until either a space or a closing " is found.
 * If properString is TRUE, the first " is lost, so we can ignore it.
 * If properString is FALSE, the first character is lost and we have to reinsert it.
 * We look for a space when properString is FALSE and we look for a " when properString is TRUE.
 * When this character is found, we return the string we read up until this point.
 */
char *readString(bool properString, char firstChar, bool *isFinished, bool *error) {
	bool properFinish = FALSE;
	int size = 0;
	char currChar;
	char *result = NULL;

	// Reinsert the first character, as mentioned in the header comment.
	if (!properString) {
		size++;
		result = realloc(result, size * sizeof(char));
		result[size - 1] = firstChar;
	}

    // Read until our exit condition, or '\n' (End of input line) is found.
	while ((currChar = getchar()) != '\n') {
		if (properString) {
			if (currChar == '"') {
				properFinish = TRUE;
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
		*error = TRUE;
		invalidSyntaxError();
	}

	// Let the main tokenize function know whether the input line ended while reading a string.
	if (currChar == '\n') {
		*isFinished = TRUE;
	}

	size++;
	result = realloc(result, size * sizeof(char));
	result[size - 1] = '\0';
	return result;
}

// Replace the string of characters in our input file by a list of tokens to allow for easier parsing/error detection.
Token *tokenize(bool *error) {
    Token *startToken = NULL;
    Token *token = NULL;
    Token *prevToken = NULL;

    char currChar;
    bool finishedReading = FALSE;

    // Continue reading until we have tokenized the entire input line.
    while (!finishedReading) {
		currChar = getchar();

		// An input line ends on a newline character.
		if (currChar == '\n') {
		    finishedReading = TRUE;
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
				token->content = readString(TRUE, '\0', &finishedReading, error);
				break;
		    // If the token didn't match any other cases, it's a regular string.
			default:
				str = readString(FALSE, currChar, &finishedReading, error);
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
