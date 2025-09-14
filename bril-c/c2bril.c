#include <stdio.h>

#include "bril.h"
#include "parser.h"

int main() {
    program_t *program = parse_program();
    emit_program(program);
    return 0;
}