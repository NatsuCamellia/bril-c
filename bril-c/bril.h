#ifndef BRIL_H
#define BRIL_H

typedef enum { OP_CONST } op_t;

typedef struct instr {
    op_t op;
    char dest[32];
    char type[32];
    int value;
    struct instr *next;
} instr_t;

typedef struct function {
    char type[32];
    char name[32];
    instr_t *instrs;
    struct function *next;
} function_t;

typedef struct {
    function_t *functions;
} program_t;

void emit_program(program_t *program);

#endif  // BRIL_H