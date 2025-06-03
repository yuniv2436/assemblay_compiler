CC = gcc
CFLAGS = -ansi -pedantic -Wall -g
OFLAGS = -c
LIBS = -I.
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
BIN = assembler

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) $(OFLAGS) $(LIBS) $< -o $@

clean:
	rm $(BIN) $(OBJS)

