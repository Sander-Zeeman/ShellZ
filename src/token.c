#include "token.h"

#include <stdio.h>
#include <stdlib.h>

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

void freeTokens(Token *token) {
    if (token != NULL) {
        freeTokens(token->next);
        if (token->content) {
            free(token->content);
        }
        free(token);
    }
}
