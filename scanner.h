#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

typedef enum {
    TOK_ID,
    TOK_NUM_INT,
    TOK_NUM_FLOAT,
    TOK_STRING,
    TOK_CHAR,
    TOK_KEYWORD,
    TOK_OP,
    TOK_DELIM,
    TOK_EOF,
    TOK_ERROR
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[256];
    int line;
} Token;

Token getToken(FILE *fp);

#endif