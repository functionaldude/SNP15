CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
LDFLAGS = 



SRC = sort.c

BIN = sort

all: CFLAGS += -O2 -fomit-frame-pointer
all: binary

debug: clean
debug: CFLAGS += -g -O0 -D DEBUG
debug: binary




binary: $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC) $(LDFLAGS)

clean:
	-rm -f $(BIN)

ddd: debug
	ddd ./$(BIN)

valgrind: debug
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes ./$(BIN)

