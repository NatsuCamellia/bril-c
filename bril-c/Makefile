CFLAGS = -Wall -Wextra -g

.phony: all clean

all: c2bril

c2bril: c2bril.o parser.o lexer.o bril.o error.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o c2bril