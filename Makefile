CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall -std=c99 -lm
PROGS=changegreedy #changeslow changedp

all: $(PROGS)

changegreedy: changegreedy.o
	$(CC) $(CFLAGS) -o changegreedy changegreedy.o

changegreedy.o: changegreedy.c
	$(CC) $(CFLAGS) -c changegreedy.c

test_cg: 
	rm -f times_cg1_10_25_50.txt
	rm -f times_cg1_2_4.txt
	./changegreedy test_file1.txt>times_cg1_10_25_50.txt
	./changegreedy test_file2.txt>times_cg1_2_4.txt

test_dp: 
	rm -f times_cdp1_10_25_50.txt
	rm -f times_cdp1_2_4.txt
	./changedp test_file1.txt>times_cdp1_10_25_50.txt
	./changedp test_file2.txt>times_cdp1_2_4.txt

test_slow: 
	rm -f times_slow1_10_25_50.txt
	rm -f times_slow1_2_4.txt
	./changeslow test_file1.txt>times_slow1_10_25_50.txt
	./changeslow test_file2.txt>times_slow1_2_4.txt


#changedp: changedp.o
#	$(CC) $(CFLAGS) -o changedp changedp.o

#changedp.o: changedp.c
#	$(CC) $(CFLAGS) -c changedp.c

#changeslow: changeslow.o
#	$(CC) $(CFLAGS) -o changeslow changeslow.o

#changeslow.o: changeslow.c
#	$(CC) $(CFLAGS) -c changeslow.c

clean:
	rm -f $(PROGS) *.o *~ *#  times_cg1_10_25_50.txt  times_cg1_2_4.txt *change.txt
