CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall -std=c99 -lm
PROGS=tsp

all: $(PROGS)

tsp: tsp.o
	$(CC) $(CFLAGS) -o tsp tsp.o

tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c


test_tsp: 
	rm -f tsp_example_4.txt.tour
	./tsp tsp_example_4.txt

clean:
	rm -f $(PROGS) *.o *~ *#  tsp_example_4.txt
