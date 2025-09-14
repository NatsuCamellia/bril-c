CFLAGS = -Wall -Wextra -g

.phony: all clean

all: c2bril

c2bril: c2bril.o parser.o lexer.o bril.o error.o
	$(CC) $(CFLAGS) -o $@ $^

c2bril.o: c2bril.c bril.h parser.h
	$(CC) $(CFLAGS) -c $<

parser.o: parser.c parser.h lexer.h bril.h error.h
	$(CC) $(CFLAGS) -c $<

lexer.o: lexer.c lexer.h error.h
	$(CC) $(CFLAGS) -c $<

bril.o: bril.c bril.h
	$(CC) $(CFLAGS) -c $<

error.o: error.c error.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o c2bril