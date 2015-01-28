
CC=gcc
DEBUG=-g
CFLAGS=$(DEBUG) -Wall -std=c99
PROGS=algo4

all: $(PROGS)

algo4: algo4.o
	$(CC) $(CFLAGS) -o algo4 algo4.o

algo4.o: algo4.c
	$(CC) $(CFLAGS) -c algo4.c

test: 
	./algo4 100
	./algo4 200
	./algo4 300
	./algo4 400
	./algo4 500
	./algo4 600
	./algo4 700
	./algo4 800
	./algo4 900
	./algo4 1000
	./algo4 2000
	./algo4 3000
	./algo4 4000
	./algo4 5000
	./algo4 6000
	./algo4 7000
	./algo4 8000
	./algo4 9000
	./algo4 10000

tests: test>test.out


testcase:  
	./algo4 10 testcase algo4>algo4.txt	
	./algo4 10 testcase algo4>algo3.txt
	./algo4 10 testcase algo4>algo2.txt
	./algo4 10 testcase algo4>algo1.txt
	diff algo4.txt algo3.txt 
	diff algo3.txt algo2.txt
	diff algo2.txt algo1.txt
	ar q MMS_file.ar algo1.txt algo2.txt algo3.txt algo4.txt
	cp MMS_file.ar MMS_Results.txt

clean:
