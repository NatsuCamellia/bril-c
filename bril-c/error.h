#ifndef ERROR_H
#define ERROR_H

#define COLOR_RESET "\e[0m"
#define COLOR_BRIGHT "\e[1m"
#define COLOR_RED "\e[31m"

extern int row;
extern int col;
extern char line_buffer[256];

void error(const char *msg, int start_col, int len);

#endif // ERROR_H