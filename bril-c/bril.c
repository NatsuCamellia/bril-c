#include <stdio.h>

#include "bril.h"

void emit_function(function_t *func) {
    // Function name
    printf("@%s", func->name);

    // Return type
    if (func->type[0]) {
        printf(": %s", func->type);
    }
    printf(" {\n");
    // Function body (currently empty)
    printf("}\n");
}

void emit_program(program_t *program) {
    function_t *func = program->functions;
    while (func) {
        emit_function(func);
        func = func->next;
    }
}