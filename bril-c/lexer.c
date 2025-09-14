#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "lexer.h"
#include "error.h"

extern int row;
extern int col;
char next_char;
char token_buffer[MAX_TOKEN_LENGTH];
int token_length = 0;

void read_char() {
    if (next_char == '\n') {
        row++;
        col = 0;
    }
    next_char = getchar();
    line_buffer[col] = next_char;
    col++;
}

static token_t _lex_token() {
    if (next_char == EOF)
        return TOKEN_EOF;

    if (isalpha(next_char) || next_char == '_') {
        token_buffer[token_length++] = next_char;
        read_char();
        while (isalnum(next_char) || next_char == '_') {
            token_buffer[token_length++] = next_char;
            read_char();
        }
        return TOKEN_ID;
    }

    if (next_char == '(') {
        read_char();
        token_buffer[token_length++] = '(';
        return TOKEN_LPAREN;
    }

    if (next_char == ')') {
        read_char();
        token_buffer[token_length++] = ')';
        return TOKEN_RPAREN;
    }

    if (next_char == '{') {
        read_char();
        token_buffer[token_length++] = '{';
        return TOKEN_LBRACE;
    }

    if (next_char == '}') {
        read_char();
        token_buffer[token_length++] = '}';
        return TOKEN_RBRACE;
    }

    char buf[64];
    snprintf(buf, sizeof(buf), "unknown start of token: " COLOR_BRIGHT "'%c'" COLOR_RESET, next_char);
    error(buf, col, 1);
    return TOKEN_EOF; // Unreachable
}

token_t lex_token() {
    // Clear buffer
    token_length = 0;
    token_buffer[0] = 0;
    while (isspace(next_char))
        read_char();
    token_t token = _lex_token();
    token_buffer[token_length] = 0; // Null-terminate the string
    return token;
}

void init_lexer() {
    row = 1;
    col = 0;
    read_char();
}