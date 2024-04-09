#pragma once

typedef enum TokenType {
    String,
    IOIn,
    IOOut,
    Background,
    Pipe,
    Exit
} TokenType;

typedef struct Token {
    char *content;
    TokenType type;
    struct Token *next;
} Token;

void printTokenType(TokenType type);
void printTokens(Token *token);
void freeTokens(Token *token);
