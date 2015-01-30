/*
	Garrett Genz, David Crisman, Kathleen Beltramini
	CS325-400
	Project 1
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> /* memset */
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <dirent.h>


//to run program enter the following after compiling with make
// ./maxsub 10 testcase algo4 //to print out results to test cases for algo4
// ./maxsub [# elements in array ] //prints out just timing results for algo 4 for 10 random arrays of element specified size
// ./maxsub [#of elements in array] printrandomarray //shows the random array and timing


struct tuple {
     int lowIndex; //holds start of max subarray
     int highIndex; //holds end of max subarray
     int sum; //holds sum of max subarray
};


void print_maxsubarray(int *test_array, int sizeofarray, struct tuple t);  //prints the array, max subarray, and sum of max subarray

struct tuple algo1(int *test_array, int sizeofarray);
struct tuple algo2(int *test_array, int sizeofarray);
struct tuple algo3(int *test_array, int sizeofarray);
struct tuple algo4(int *test_array, int sizeofarray);


//from: http://stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c
//pulled random generator out so seed set up properly.
//function provides a random number between a min and a max
int random_number(int min_num, int max_num)
        {
            int result=0,low_num=0,hi_num=0;
            if(min_num<max_num)
            {
                low_num=min_num;
                hi_num=max_num+1; // this is done to include max_num in output.
            }else{
                low_num=max_num+1;// this is done to include max_num in output.
                hi_num=min_num;
            }
            result = (rand()%(hi_num-low_num))+low_num;
            return result;
        }


//Takes in the arguments from the command lines and provides parameters to functions
//can add command line argument to tell whether to generate random array or use provided test cases.
int main(int argc, char **argv) 
{
	struct tuple s;
	clock_t start, end;
	srand(time(NULL));
	int sizeofarray;
	char size_string[10];
	strcpy(size_string,argv[1]); 
	sizeofarray=atoi(size_string);
	int k;


	//prints results for test cases for algo1 provided in MSS_Problems.txt
	if ((argc==4) && (strcmp(argv[2],"testcase")==0) && (strcmp(argv[3],"algo1")==0))  //test cases for algo1
	{
		//test case 1:
		int test_case1[36]= {1, 2, 4, -1, 4, -10, 4, -19, 18, -1, -3, -4, 11, 3, -20, 19, -33, 50, 66, -22, -4, -55, 91, 100, -102, 9, 10, 19, -10, 10, 11, 11, -10, -18, 50, 90};
		int sizeofarray1 = sizeof(test_case1)/sizeof(int);
		struct tuple s1;
		s1=algo1(test_case1,sizeofarray1);
		print_maxsubarray(test_case1, sizeofarray1, s1);

		//test case 2:
		int test_case2[22]= {12, 12, 14, -88, -1, 45, 6, 8, -33, 2, 8, -9, -33, -8, -23, -77, -89, 1, 9, 10, 92, 87};
		int sizeofarray2 = sizeof(test_case2)/sizeof(int);
		struct tuple s2;
		s2=algo1(test_case2,sizeofarray2);
		print_maxsubarray(test_case2, sizeofarray2, s2);


		//test case 3:
		int test_case3[21]= {565, 78, 33, 9, 10, 84, 71, -4, -22, -55, -10, 76, -9, -9, -11, 76, 89, 11, 10, -33, 9};
		int sizeofarray3 = sizeof(test_case3)/sizeof(int);
		struct tuple s3;
		s3=algo1(test_case3,sizeofarray3);
		print_maxsubarray(test_case3, sizeofarray3, s3);
	
		//test case 4:
		int test_case4[31]= {2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
		int sizeofarray4 = sizeof(test_case4)/sizeof(int);
		struct tuple s4;
		s4=algo1(test_case4,sizeofarray4);
		print_maxsubarray(test_case4, sizeofarray4, s4);


		//test case 5:
		int test_case5[1]= {2};
		int sizeofarray5 = sizeof(test_case5)/sizeof(int);
		struct tuple s5;
		s5=algo1(test_case5,sizeofarray5);
		print_maxsubarray(test_case5, sizeofarray5, s5);


		//test case 6:
		int test_case6[17]= {-1, -1, -1, -1, -1, -100, -10, -10, 100, 100, 100, 100, -100, 100, 10, -10, -1};
		int sizeofarray6 = sizeof(test_case6)/sizeof(int);
		struct tuple s6;
		s6=algo1(test_case6,sizeofarray6);
		print_maxsubarray(test_case6, sizeofarray6, s6);

		//test case 7:
		int test_case7[29]= {12, 23, 44, -17, 12, 14, -88, -1, 45, 6, 8, -33, 2, 8, -9, -33, -8, -23, -77, -89, 1, 9, 13, -25, 10, 92, 57, 99, -22};
		int sizeofarray7 = sizeof(test_case7)/sizeof(int);
		struct tuple s7;
		s7=algo1(test_case7,sizeofarray7);
		print_maxsubarray(test_case7, sizeofarray7, s7);

	}

	//prints results for test cases for algo2 provided in MSS_Problems.txt
	else if ((argc==4) && (strcmp(argv[2],"testcase")==0) && (strcmp(argv[3],"algo2")==0))  //test cases for algo2
	{
		//test case 1:
		int test_case1[36]= {1, 2, 4, -1, 4, -10, 4, -19, 18, -1, -3, -4, 11, 3, -20, 19, -33, 50, 66, -22, -4, -55, 91, 100, -102, 9, 10, 19, -10, 10, 11, 11, -10, -18, 50, 90};
		int sizeofarray1 = sizeof(test_case1)/sizeof(int);
		struct tuple s1;
		s1=algo2(test_case1,sizeofarray1);
		print_maxsubarray(test_case1, sizeofarray1, s1);

		//test case 2:
		int test_case2[22]= {12, 12, 14, -88, -1, 45, 6, 8, -33, 2, 8, -9, -33, -8, -23, -77, -89, 1, 9, 10, 92, 87};
		int sizeofarray2 = sizeof(test_case2)/sizeof(int);
		struct tuple s2;
		s2=algo2(test_case2,sizeofarray2);
		print_maxsubarray(test_case2, sizeofarray2, s2);


		//test case 3:
		int test_case3[21]= {565, 78, 33, 9, 10, 84, 71, -4, -22, -55, -10, 76, -9, -9, -11, 76, 89, 11, 10, -33, 9};
		int sizeofarray3 = sizeof(test_case3)/sizeof(int);
		struct tuple s3;
		s3=algo2(test_case3,sizeofarray3);
		print_maxsubarray(test_case3, sizeofarray3, s3);
	
		//test case 4:
		int test_case4[31]= {2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
		int sizeofarray4 = sizeof(test_case4)/sizeof(int);
		struct tuple s4;
		s4=algo2(test_case4,sizeofarray4);
		print_maxsubarray(test_case4, sizeofarray4, s4);


		//test case 5:
		int test_case5[1]= {2};
		int sizeofarray5 = sizeof(test_case5)/sizeof(int);
		struct tuple s5;
		s5=algo2(test_case5,sizeofarray5);
		print_maxsubarray(test_case5, sizeofarray5, s5);


		//test case 6:
		int test_case6[17]= {-1, -1, -1, -1, -1, -100, -10, -10, 100, 100, 100, 100, -100, 100, 10, -10, -1};
		int sizeofarray6 = sizeof(test_case6)/sizeof(int);
		struct tuple s6;
		s6=algo2(test_case6,sizeofarray6);
		print_maxsubarray(test_case6, sizeofarray6, s6);

		//test case 7:
		int test_case7[29]= {12, 23, 44, -17, 12, 14, -88, -1, 45, 6, 8, -33, 2, 8, -9, -33, -8, -23, -77, -89, 1, 9, 13, -25, 10, 92, 57, 99, -22};
		int sizeofarray7 = sizeof(test_case7)/sizeof(int);
		struct tuple s7;
		s7=algo2(test_case7,sizeofarray7);
		print_maxsubarray(test_case7, sizeofarray7, s7);

	}
	//prints results for test cases for algo3 provided in MSS_Problems.txt
	else if ((argc==4) && (strcmp(argv[2],"testcase")==0) && (strcmp(argv[3],"algo3")==0))  //test cases for algo1
	{
		//test case 1:
		int test_case1[36]= {1, 2, 4, -1, 4, -10, 4, -19, 18, -1, -3, -4, 11, 3, -20, 19, -33, 50, 66, -22, -4, -55, 91, 100, -102, 9, 10, 19, -10, 10, 11, 11, -10, -18, 50, 90};
		int sizeofarray1 = sizeof(test_case1)/sizeof(int);
		struct tuple s1;
		s1=algo3(test_case1,sizeofarray1);
		print_maxsubarray(test_case1, sizeofarray1, s1);

		//test case 2:
		int test_case2[22]= {12, 12, 14, -88, -1, 45, 6, 8, -33, 2, 8, -9, -33, -8, -23, -77, -89, 1, 9, 10, 92, 87};
		int sizeofarray2 = sizeof(test_case2)/sizeof(int);
		struct tuple s2;
		s2=algo1(test_case2,sizeofarray2);
		print_maxsubarray(test_case2, sizeofarray2, s2);


		//test case 3:
		int test_case3[21]= {565, 78, 33, 9, 10, 84, 71, -4, -22, -55, -10, 76, -9, -9, -11, 76, 89, 11, 10, -33, 9};
		int sizeofarray3 = sizeof(test_case3)/sizeof(int);
		struct tuple s3;
		s3=algo3(test_case3,sizeofarray3);
		print_maxsubarray(test_case3, sizeofarray3, s3);
	
		//test case 4:
		int test_case4[31]= {2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
		int sizeofarray4 = sizeof(test_case4)/sizeof(int);
		struct tuple s4;
		s4=algo3(test_case4,sizeofarray4);
		print_maxsubarray(test_case4, sizeofarray4, s4);


		//test case 5:
		int test_case5[1]= {2};
		int sizeofarray5 = sizeof(test_case5)/sizeof(int);
		struct tuple s5;
		s5=algo3(test_case5,sizeofarray5);
		print_maxsubarray(test_case5, sizeofarray5, s5);


		//test case 6:
		int test_case6[17]= {-1, -1, -1, -1, -1, -100, -10, -10, 100, 100, 100, 100, -100, 100, 10, -10, -1};
		int sizeofarray6 = sizeof(test_case6)/sizeof(int);
		struct tuple s6;
		s6=algo3(test_case6,sizeofarray6);
		print_maxsubarray(test_case6, sizeofarray6, s6);

		//test case 7:
		int test_case7[29]= {12, 23, 44, -17, 12, 14, -88, -1, 45, 6, 8, -33, 2, 8, -9, -33, -8, -23, -77, -89, 1, 9, 13, -25, 10, 92, 57, 99, -22};
		int sizeofarray7 = sizeof(test_case7)/sizeof(int);
		struct tuple s7;
		s7=algo3(test_case7,sizeofarray7);
		print_maxsubarray(test_case7, sizeofarray7, s7);

	}

	//prints results for test cases provided in MSS_Problems.txt
	else if ((argc==4) && (strcmp(argv[2],"testcase")==0) && (strcmp(argv[3],"algo4")==0))  //test cases for algo4
	{
		//test case 1:
		int test_case1[36]= {1, 2, 4, -1, 4, -10, 4, -19, 18, -1, -3, -4, 11, 3, -20, 19, -33, 50, 66, -22, -4, -55, 91, 100, -102, 9, 10, 19, -10, 10, 11, 11, -10, -18, 50, 90};
		int sizeofarray1 = sizeof(test_case1)/sizeof(int);
		struct tuple s1;
		s1=algo4(test_case1,sizeofarray1);
		print_maxsubarray(test_case1, sizeofarray1, s1);

		//test case 2:
		int test_case2[22]= {12, 12, 14, -88, -1, 45, 6, 8, -33, 2, 8, -9, -33, -8, -23, -77, -89, 1, 9, 10, 92, 87};
		int sizeofarray2 = sizeof(test_case2)/sizeof(int);
		struct tuple s2;
		s2=algo4(test_case2,sizeofarray2);
		print_maxsubarray(test_case2, sizeofarray2, s2);


		//test case 3:
		int test_case3[21]= {565, 78, 33, 9, 10, 84, 71, -4, -22, -55, -10, 76, -9, -9, -11, 76, 89, 11, 10, -33, 9};
		int sizeofarray3 = sizeof(test_case3)/sizeof(int);
		struct tuple s3;
		s3=algo4(test_case3,sizeofarray3);
		print_maxsubarray(test_case3, sizeofarray3, s3);
	
		//test case 4:
		int test_case4[31]= {2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
		int sizeofarray4 = sizeof(test_case4)/sizeof(int);
		struct tuple s4;
		s4=algo4(test_case4,sizeofarray4);
		print_maxsubarray(test_case4, sizeofarray4, s4);


		//test case 5:
		int test_case5[1]= {2};
		int sizeofarray5 = sizeof(test_case5)/sizeof(int);
		struct tuple s5;
		s5=algo4(test_case5,sizeofarray5);
		print_maxsubarray(test_case5, sizeofarray5, s5);


		//test case 6:
		int test_case6[17]= {-1, -1, -1, -1, -1, -100, -10, -10, 100, 100, 100, 100, -100, 100, 10, -10, -1};
		int sizeofarray6 = sizeof(test_case6)/sizeof(int);
		struct tuple s6;
		s6=algo4(test_case6,sizeofarray6);
		print_maxsubarray(test_case6, sizeofarray6, s6);

		//test case 7:
		int test_case7[29]= {12, 23, 44, -17, 12, 14, -88, -1, 45, 6, 8, -33, 2, 8, -9, -33, -8, -23, -77, -89, 1, 9, 13, -25, 10, 92, 57, 99, -22};
		int sizeofarray7 = sizeof(test_case7)/sizeof(int);
		struct tuple s7;
		s7=algo4(test_case7,sizeofarray7);
		print_maxsubarray(test_case7, sizeofarray7, s7);

	}

	//computes results for the specified array size
	else
	{
		if ((argc==3) && (strcmp(argv[2],"algo1")==0))  //test cases for algo4
		{
			for (k=0; k<10; k++)
			{
				int t=0;
				int array[sizeofarray];
				//printf("%d. ", (k+1));
				while (t<sizeofarray)
				{
					array[t]= random_number(-100,100);  //generates random numbers between -100 and 100
					t++;
				}
				start = clock();
				s= algo1(array,sizeofarray);
				end = clock();
				double cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC*1000);
				printf("1, %d, %.2f\n", sizeofarray, cpu_time_used);		        
				if ((argc==3)&&(strcmp(argv[2],"printrandomarray")==0))
				print_maxsubarray(array, sizeofarray, s);
			}
		}
		else if ((argc==3) && (strcmp(argv[2],"algo2")==0))  //test cases for algo4
		{
			for (k=0; k<10; k++)
			{
				int t=0;
				int array[sizeofarray];
				//printf("%d. ", (k+1));
				while (t<sizeofarray)
				{
					array[t]= random_number(-100,100);  //generates random numbers between -100 and 100
					t++;
				}
				start = clock();
				s= algo2(array,sizeofarray);
				end = clock();
				double cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC*1000);
				printf("2, %d, %.2f\n", sizeofarray, cpu_time_used);		        
				if ((argc==3)&&(strcmp(argv[2],"printrandomarray")==0))
				print_maxsubarray(array, sizeofarray, s);
			}
		}
		else if ((argc==3) && (strcmp(argv[2],"algo3")==0))  //test cases for algo4
		{
			for (k=0; k<10; k++)
			{
				int t=0;
				int array[sizeofarray];
				//printf("%d. ", (k+1));
				while (t<sizeofarray)
				{
					array[t]= random_number(-100,100);  //generates random numbers between -100 and 100
					t++;
				}
				start = clock();
				s= algo3(array,sizeofarray);
				end = clock();
				double cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC*1000);
				printf("3, %d, %.2f\n", sizeofarray, cpu_time_used);		        
				if ((argc==3)&&(strcmp(argv[2],"printrandomarray")==0))
				print_maxsubarray(array, sizeofarray, s);
			}
		}
		else if ((argc==3) && (strcmp(argv[2],"algo4")==0))  //test cases for algo4
		{
			for (k=0; k<10; k++)
			{
				int t=0;
				int array[sizeofarray];
				//printf("%d. ", (k+1));
				while (t<sizeofarray)
				{
					array[t]= random_number(-100,100);  //generates random numbers between -100 and 100
					t++;
				}
				start = clock();
				s= algo4(array,sizeofarray);
				end = clock();
				double cpu_time_used = ((double)(end - start)) / (CLOCKS_PER_SEC*1000);
				printf("4, %d, %.2f\n", sizeofarray, cpu_time_used);		        
				if ((argc==3)&&(strcmp(argv[2],"printrandomarray")==0))
				print_maxsubarray(array, sizeofarray, s);
			}
		}

	}

}

void print_maxsubarray(int *test_array, int sizeofarray, struct tuple t)
{
	int m, i, j;
	m=0;
	printf("\n[");
	while (m<sizeofarray)
	{
		printf("%d", test_array[m]);
		if (m!=(sizeofarray-1))
			printf(",");
		m++;
	}
	printf("],[");
	i = t.lowIndex;
	j = t.highIndex;
	if(i == 0 && t.sum==0)
	{
		printf(" (empty),  0\n");
	}
	else
	{
		while(i<=j)
		{
			printf("%d", test_array[i]);
			if (i<j)
				printf(",");
			i++;
		}	
		printf("], %d\n", t.sum);
	}

}

//function for algorithm 4 using kadane's algorithm explained: http://en.wikipedia.org/wiki/Maximum_subarray_problem
//inputs are the array to compute and the size of the array
//returns the start and end of subarray and sum of elements in array
struct tuple algo4(int *test_array, int sizeofarray)
{
	struct tuple d; //holds start, end and sum of subarray
	assert (sizeofarray != 0); //verifies that the array is not null
	int max_ending_here;  //used to check if the max at index is greater than the current_max
	int max_start = 0; //holds the start of the max subarray, initialized to position 0
	int current_max; //will hold the final max sum
	int endpoint; //holds the end of the max subarray while being computed
	current_max = max_ending_here = 0; //initializes to 0
	int i; //for iterating through array
	int current_start=0; //used to track changes in the max subarray start index
	for (i=0; i< sizeofarray; i++) //iterates through array
	{
		if(max_ending_here<0) //in case the sum is < 0
		{	max_ending_here = 0;
			current_start=i;  
		}

		max_ending_here = max_ending_here + test_array[i]; //adds current element in index
		
		if (current_max < max_ending_here)
		{	current_max = max_ending_here;  //tracks the sum of max subarray
			max_start = current_start; //tracks the start of subarray 
			endpoint = i;	//tracks the end of max subarray
		}
	}
	
	d.lowIndex=max_start; //sets the final start of the max subarray index to be returned
	d.highIndex=endpoint; //sets the final end of the max subarray index to be returned
	d.sum=current_max; //sets the final sum ob maxsubarray index to be returned

	return d; //returns struct d

}		

struct tuple algo3(int *test_array, int sizeofarray)
{
	struct tuple d; //holds start, end and sum of subarray
	assert (sizeofarray != 0); //verifies that the array is not null
	int max_ending_here;  //used to check if the max at index is greater than the current_max
	int max_start = 0; //holds the start of the max subarray, initialized to position 0
	int current_max; //will hold the final max sum
	int endpoint; //holds the end of the max subarray while being computed
	current_max = max_ending_here = 0; //initializes to 0
	int i; //for iterating through array
	int current_start=0; //used to track changes in the max subarray start index
	for (i=0; i< sizeofarray; i++) //iterates through array
	{
		if(max_ending_here<0) //in case the sum is < 0
		{	max_ending_here = 0;
			current_start=i;  
		}

		max_ending_here = max_ending_here + test_array[i]; //adds current element in index
		
		if (current_max < max_ending_here)
		{	current_max = max_ending_here;  //tracks the sum of max subarray
			max_start = current_start; //tracks the start of subarray 
			endpoint = i;	//tracks the end of max subarray
		}
	}
	
	d.lowIndex=max_start; //sets the final start of the max subarray index to be returned
	d.highIndex=endpoint; //sets the final end of the max subarray index to be returned
	d.sum=current_max; //sets the final sum ob maxsubarray index to be returned

	return d; //returns struct d

}

struct tuple algo2(int *test_array, int sizeofarray)
{
	struct tuple d; //holds start, end and sum of subarray
	assert (sizeofarray != 0); //verifies that the array is not null
	int max_ending_here;  //used to check if the max at index is greater than the current_max
	int max_start = 0; //holds the start of the max subarray, initialized to position 0
	int current_max; //will hold the final max sum
	int endpoint; //holds the end of the max subarray while being computed
	current_max = max_ending_here = 0; //initializes to 0
	int i; //for iterating through array
	int current_start=0; //used to track changes in the max subarray start index
	for (i=0; i< sizeofarray; i++) //iterates through array
	{
		if(max_ending_here<0) //in case the sum is < 0
		{	max_ending_here = 0;
			current_start=i;  
		}

		max_ending_here = max_ending_here + test_array[i]; //adds current element in index
		
		if (current_max < max_ending_here)
		{	current_max = max_ending_here;  //tracks the sum of max subarray
			max_start = current_start; //tracks the start of subarray 
			endpoint = i;	//tracks the end of max subarray
		}
	}
	
	d.lowIndex=max_start; //sets the final start of the max subarray index to be returned
	d.highIndex=endpoint; //sets the final end of the max subarray index to be returned
	d.sum=current_max; //sets the final sum ob maxsubarray index to be returned

	return d; //returns struct d

}

struct tuple algo1(int *test_array, int sizeofarray)
{
	struct tuple d; //holds start, end and sum of subarray
	assert (sizeofarray != 0); //verifies that the array is not null
	int max_ending_here;  //used to check if the max at index is greater than the current_max
	int max_start = 0; //holds the start of the max subarray, initialized to position 0
	int current_max; //will hold the final max sum
	int endpoint; //holds the end of the max subarray while being computed
	current_max = max_ending_here = 0; //initializes to 0
	int i; //for iterating through array
	int current_start=0; //used to track changes in the max subarray start index
	for (i=0; i< sizeofarray; i++) //iterates through array
	{
		if(max_ending_here<0) //in case the sum is < 0
		{	max_ending_here = 0;
			current_start=i;  
		}

		max_ending_here = max_ending_here + test_array[i]; //adds current element in index
		
		if (current_max < max_ending_here)
		{	current_max = max_ending_here;  //tracks the sum of max subarray
			max_start = current_start; //tracks the start of subarray 
			endpoint = i;	//tracks the end of max subarray
		}
	}
	
	d.lowIndex=max_start; //sets the final start of the max subarray index to be returned
	d.highIndex=endpoint; //sets the final end of the max subarray index to be returned
	d.sum=current_max; //sets the final sum ob maxsubarray index to be returned

	return d; //returns struct d

}

