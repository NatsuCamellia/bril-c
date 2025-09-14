#include "bril.h"

#include <stdio.h>

void emit_function(function_t *func) {
    // Function name
    printf("@%s", func->name);

    // Return type
    if (func->type[0]) {
        printf(": %s", func->type);
    }
    printf(" {\n");
    // Function body
    instr_t *instr = func->instrs;
    while (instr) {
        if (instr->op == OP_CONST) {
            printf("  %s: %s = const %d;\n", instr->dest, instr->type,
                   instr->value);
        }
        instr = instr->next;
    }
    printf("}\n");
}

void emit_program(program_t *program) {
    function_t *func = program->functions;
    while (func) {
        emit_function(func);
        func = func->next;
    }
}