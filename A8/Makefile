CC=gcc
CFLAGS=-g -c -Wall -std=gnu11
LDFLAGS=
SOURCES=$(wildcard *.c)
OBJECTS=${SOURCES:.c=.o}

.PHONY : all clean

# make all
all: vendor speed

# make
speed: speed.o
	$(CC) -g -o $@ $^ $(LDFLAGS)

# make
vendor: vendor.o
	$(CC) -g -o $@ $^ $(LDFLAGS)

# make %.o
%.o: %.c
	$(CC) $(CFLAGS) -o $@ $< -MMD -MF ./$@.d $(LDFLAGS)

# make clean
clean :
	rm -f *.o *.d speed vendor

-include $(wildcard ./*.d)
