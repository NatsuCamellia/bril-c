#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bril.h"
#include "error.h"
#include "lexer.h"

token_t next_token;

void read_token() { next_token = lex_token(); }

void expect_token(token_t expected) {
    if (next_token != expected) {
        char buf[256];
        snprintf(buf, sizeof(buf),
                 "expected token " COLOR_BRIGHT "%s" COLOR_RESET
                 ", got " COLOR_BRIGHT "%s" COLOR_RESET,
                 token_name[expected], token_name[next_token]);
        error(buf, col - token_length, token_length);
    }
}

void check_type() {
    if (strcmp(token_buffer, "int") == 0) return;
    fprintf(stderr, "Unknown type: %s\n", token_buffer);
    exit(1);
}

instr_t *parse_stmt() {
    instr_t *instr = malloc(sizeof(instr_t));

    if (next_token == TOKEN_ID) {
        if (strcmp(token_buffer, "int") == 0) {
            // Variable declaration
            strcpy(instr->type, token_buffer);
            read_token();
            expect_token(TOKEN_ID);
            strcpy(instr->dest, token_buffer);
            read_token();
            expect_token(TOKEN_ASSIGN);
            read_token();
            expect_token(TOKEN_INTLIT);
            instr->op = OP_CONST;
            instr->value = atoi(token_buffer);
            read_token();
            expect_token(TOKEN_SEMICOLON);
            read_token();
            instr->next = NULL;
            return instr;
        }
    }

    error("unknown statement", col - token_length, token_length);
    return NULL;  // Unreachable
}

function_t *parse_function() {
    function_t *func = malloc(sizeof(function_t));
    // Type
    expect_token(TOKEN_ID);
    check_type();
    strcpy(func->type, token_buffer);
    read_token();

    // Name
    expect_token(TOKEN_ID);
    strcpy(func->name, token_buffer);
    func->next = NULL;
    read_token();

    // Params (currently ignored)
    expect_token(TOKEN_LPAREN);
    read_token();
    expect_token(TOKEN_RPAREN);
    read_token();

    // Body (currently ignored)
    expect_token(TOKEN_LBRACE);
    read_token();
    func->instrs = NULL;
    instr_t **pprev = &func->instrs;
    while (next_token != TOKEN_RBRACE) {
        instr_t *instr = parse_stmt();
        *pprev = instr;
        while (instr->next) instr = instr->next;
        pprev = &instr->next;
    }
    expect_token(TOKEN_RBRACE);
    read_token();

    return func;
}

program_t *parse_program() {
    init_lexer();
    read_token();

    program_t *program = malloc(sizeof(program_t));
    function_t **pprev = &program->functions;
    while (next_token != TOKEN_EOF) {
        function_t *func = parse_function();
        *pprev = func;
        pprev = &func->next;
    }
    return program;
}