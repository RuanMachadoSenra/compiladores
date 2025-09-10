#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"

static int line = 1;

const char *keywords[] = { "if","else","begin","end","int","float","char","program","var",
                           "procedure","function","while","return","then","read","write" };
const int keywordsCount = 15;

int isKeyword(const char *lexeme) {
    for (int i=0;i<keywordsCount;i++)
        if (strcmp(lexeme, keywords[i])==0) return 1;
    return 0;
}

Token getToken(FILE *fp) {
    Token token;
    int c;
    int i=0;

    while ((c = fgetc(fp)) != EOF) {
        if (c==' ' || c=='\t') continue;
        else if (c=='\n') { line++; continue; }
        else break;
    }

    if (c==EOF) {
        token.type = TOK_EOF;
        strcpy(token.lexeme, "EOF");
        token.line = line;
        return token;
    }

    // Identificador ou palavra-chave
    if (isalpha(c) || c=='_') {
        token.lexeme[i++] = c;
        while (isalnum(c = fgetc(fp)) || c=='_') token.lexeme[i++] = c;
        ungetc(c, fp);
        token.lexeme[i] = '\0';
        token.line = line;
        token.type = isKeyword(token.lexeme) ? TOK_KEYWORD : TOK_ID;
        return token;
    }

    // Número inteiro ou float simples
    if (isdigit(c)) {
        token.lexeme[i++] = c;
        int isFloat = 0;
        while (isdigit(c = fgetc(fp))) token.lexeme[i++] = c;
        if (c=='.') {
            isFloat = 1;
            token.lexeme[i++] = c;
            while (isdigit(c = fgetc(fp))) token.lexeme[i++] = c;
        }
        ungetc(c, fp);
        token.lexeme[i] = '\0';
        token.type = isFloat ? TOK_NUM_FLOAT : TOK_NUM_INT;
        token.line = line;
        return token;
    }

    // Outros casos simples
    token.lexeme[i++] = c;
    token.lexeme[i] = '\0';
    token.type = TOK_ERROR;
    token.line = line;
    return token;
}