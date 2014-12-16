CC=gcc
CFLAGS=-c -Wall -std=c99 -g
TITLE=malloc_example

.PHONY : all clean

# make all
all: $(TITLE) test

# make
$(TITLE): malloc.o example.o
	$(CC) malloc.o example.o -o $(TITLE)

example.o: example.c malloc.c
	$(CC) $(CFLAGS) example.c malloc.c

malloc.o: malloc.c
	$(CC) $(CFLAGS) malloc.c

test:
	cd ./tests/ && $(MAKE)

# make clean
clean :
	rm -f *.o *.d $(TITLE)
	cd ./tests/ && $(MAKE) clean
 