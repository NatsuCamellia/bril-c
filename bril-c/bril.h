#ifndef BRIL_H
#define BRIL_H

typedef struct function {
    char type[32];
    char name[32];
    struct function *next;
} function_t;

typedef struct {
    function_t *functions;
} program_t;

void emit_program(program_t *program);

#endif // BRIL_H