CC=gcc -Wall

PROGRAMMES=main

all: $(PROGRAMMES)

%.o: %.c
	$(CC) -c $<

main.o:  main.c  reading.h  stack.h  hash_table.c

reading.o: reading.c reading.h stack.h hash_table.h

stack.o: stack.c stack.h

hash_table.o: hash_table.c hash_table.h

######################################################################
#                      Edition of flows                    #
######################################################################

main: main.o reading.o stack.o hash_table.o
	$(CC) $^ -o $@

reading: reading.o stack.o hash_table.o
	$(CC) $^ -o $@

stack: stack.o
	$(CC) $^ -o $@
hash_table: hash_table.o
	$(CC) $^ -o $@

clean:
	rm -f $(PROGRAMMES) *.o