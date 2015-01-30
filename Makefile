
CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall -std=c99
PROGS=maxsub

all: $(PROGS)

maxsub: maxsub.o
	$(CC) $(CFLAGS) -o maxsub maxsub.o

maxsub.o: maxsub.c
	$(CC) $(CFLAGS) -c maxsub.c

test1: 
	./maxsub 100 algo1
	./maxsub 200 algo1
	./maxsub 300 algo1
	./maxsub 400 algo1
	./maxsub 500 algo1
	./maxsub 600 algo1
	./maxsub 700 algo1
	./maxsub 800 algo1
	./maxsub 900 algo1
	./maxsub 1000 algo1
	./maxsub 2000 algo1
	./maxsub 3000 algo1
	./maxsub 4000 algo1
	./maxsub 5000 algo1
	./maxsub 6000 algo1
	./maxsub 7000 algo1
	./maxsub 8000 algo1
	./maxsub 9000 algo1
	./maxsub 10000 algo1



test2: 
	./maxsub 100 algo2
	./maxsub 200 algo2
	./maxsub 300 algo2
	./maxsub 400 algo2
	./maxsub 500 algo2
	./maxsub 600 algo2
	./maxsub 700 algo2
	./maxsub 800 algo2
	./maxsub 900 algo2
	./maxsub 1000 algo2
	./maxsub 2000 algo2
	./maxsub 3000 algo2
	./maxsub 4000 algo2
	./maxsub 5000 algo2
	./maxsub 6000 algo2
	./maxsub 7000 algo2
	./maxsub 8000 algo2
	./maxsub 9000 algo2
	./maxsub 10000 algo2


test3: 
	./maxsub 100 algo3
	./maxsub 200 algo3
	./maxsub 300 algo3
	./maxsub 400 algo3
	./maxsub 500 algo3
	./maxsub 600 algo3
	./maxsub 700 algo3
	./maxsub 800 algo3
	./maxsub 900 algo3
	./maxsub 1000 algo3
	./maxsub 2000 algo3
	./maxsub 3000 algo3
	./maxsub 4000 algo3
	./maxsub 5000 algo3
	./maxsub 6000 algo3
	./maxsub 7000 algo3
	./maxsub 8000 algo3
	./maxsub 9000 algo3
	./maxsub 10000 algo3


test4: 
	./maxsub 100 algo4
	./maxsub 200 algo4
	./maxsub 300 algo4
	./maxsub 400 algo4
	./maxsub 500 algo4
	./maxsub 600 algo4
	./maxsub 700 algo4
	./maxsub 800 algo4
	./maxsub 900 algo4
	./maxsub 1000 algo4
	./maxsub 2000 algo4
	./maxsub 3000 algo4
	./maxsub 4000 algo4
	./maxsub 5000 algo4
	./maxsub 6000 algo4
	./maxsub 7000 algo4
	./maxsub 8000 algo4
	./maxsub 9000 algo4
	./maxsub 10000 algo4

testcase:  
	rm -f algo1.txt algo2.txt algo3.txt algo4.txt MMS_file.ar MMS_Results.txt
	./maxsub 10 testcase algo4>algo4.txt	
	./maxsub 10 testcase algo3>algo3.txt
	./maxsub 10 testcase algo2>algo2.txt
	./maxsub 10 testcase algo1>algo1.txt
	diff algo4.txt algo3.txt 
	diff algo3.txt algo2.txt
	diff algo2.txt algo1.txt
	ar q MMS_file.ar algo1.txt algo2.txt algo3.txt algo4.txt
	cp MMS_file.ar MMS_Results.txt

clean:
	rm -f $(PROGS) *.o *~ *# algo4.txt algo3.txt algo2.txt algo1.txt test.out MMS_file.ar MMS_Results.txt
