/*
David Crisman
Garrett Genz
Kathleen Beltramini
CS325 - W2015
Project Group 6
Project 2
*/

ASSUMPTIONS:
1) The input files should follow the spec exactly in order to be parsed correctly - no additional spaces or lines are allowed.
2) The coin denominations should work for the value provided that needs change.  For example, you cannot ask for change for 23 and only have 2,4, and 6 as the 
coins.


To run these programs, you can do the following:

1) We've supplied a make file. To compile all 3 programs type "make" on the command line.

2) To clean your directory, type "make clean".

3) To run Question 4 and 5, you need to make sure that you've added our 2 test files:

test_file1.txt: includes 2000 ... 3000 results for [1,10,25,50]
test_file2.txt: includes 2000 ... 3000 results for [1,3,4]

You can run all 3 algo files as once with:  

"make test_all"

If you would like to run the tests individually, you can do:

"make test_slow" - Algo 1

"make test_cg"  - Greedy Algorithm

"make test_dp" - Dynamic Programming Algorithm

When you run these tests, 4 files will be greated per alogrithm.  They are named as follows:

test_file1change.txt (as per requirements, change is added after the file name)
test_file2change.txt


The timings for the alorithms for the 2 test files are outputted:

For algo 1:

times_slow1_10_25_50.txt (for coins 1, 10, 25, 50)
times_slow1_3_4.txt (for coins 1,3,4)


For greedy algorithm:

times_cg1_10_25_50.txt (for coins 1, 10, 25, 50)
times_cg1_3_4.txt (for coin 1,3, 4)


For dynamic programming:

times_cdp1_10_25_50.txt (for coins 1,10,25, 50)
times_cdp1_3_4.txt (for coins 1,3,4)


4) To run your own tests, you can run ./changegreedy [filename].txt.  The output will go to  [filename]change.txt.


