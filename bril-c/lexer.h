#ifndef LEXER_H
#define LEXER_H

#define MAX_TOKEN_LENGTH 256

typedef enum {
    TOKEN_EOF,
    TOKEN_ID,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
} token_t;

extern char *token_name[];

typedef struct token_info {
    token_t type;
    char lexeme[MAX_TOKEN_LENGTH];
} token_info_t;

extern char token_buffer[MAX_TOKEN_LENGTH];
extern int token_length;

void init_lexer();
token_t lex_token();

#endif  // LEXER_H