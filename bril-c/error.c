#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"

#define LINE_BUFFER_SIZE 256

int row;
int col;
char line_buffer[LINE_BUFFER_SIZE];

void error(const char *msg, int start_col, int len) {
    fprintf(stderr, COLOR_BRIGHT "stdin:%d:%d: " COLOR_RED "error: " COLOR_RESET "%s\n", row, start_col, msg);

    start_col -= 1; // Convert to 0-based index
    // Get the whole line, including '\n'
    fgets(line_buffer + col, LINE_BUFFER_SIZE - col, stdin);

    // Highlight the error position
    char new_buffer[LINE_BUFFER_SIZE];
    int i = 0;
    char *ptr = new_buffer;

    ptr = stpncpy(ptr, line_buffer, start_col);
    // Color the error part in red
    ptr = stpncpy(ptr, COLOR_RED, strlen(COLOR_RED));
    ptr = stpncpy(ptr, line_buffer + start_col, len);
    ptr = stpncpy(ptr, COLOR_RESET, strlen(COLOR_RESET));
    ptr = stpcpy(ptr, line_buffer + start_col + len);


    fprintf(stderr, "%5d | %s", row, new_buffer);
    fprintf(stderr, "      | ");
    for (i = 0; i < start_col; i++)
        fprintf(stderr, " ");
    fprintf(stderr, COLOR_RED);
    fprintf(stderr, "^");
    for (i = 1; i < len; i++)
        fprintf(stderr, "~");
    fprintf(stderr, COLOR_RESET);
    fprintf(stderr, "\n");

    exit(1);
}