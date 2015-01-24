
CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall -std=c99
PROGS=algo4

all: $(PROGS)

algo4: algo4.o
	$(CC) $(CFLAGS) -o algo4 algo4.o

algo4.o: algo4.c
	$(CC) $(CFLAGS) -c algo4.c
