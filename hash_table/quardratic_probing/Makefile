CC=gcc
CFLAGS=-Wall -g
BIN=main

$(BIN):main.o hash.o
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o 
