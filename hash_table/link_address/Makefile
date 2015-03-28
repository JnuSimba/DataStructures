CC=gcc
CFLAGS=-Wall -g
BIN=hash_link_main

$(BIN):hash_link_main.o hash_link.o
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o 
