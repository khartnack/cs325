/*
	Kathleen Beltramini
	beltramk@onid.oregonstate.edu
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


struct tuple {
     int lowIndex;
     int highIndex;
     int sum;
};


void print_maxsubarray(int *test_array, int sizeofarray, struct tuple t);

struct tuple algo4(int *test_array, int sizeofarray);

//Assumes array must have at least 1 positive number.


//from: http://stackoverflow.com/questions/822323/how-to-generate-a-random-number-in-c
//pulled random generator out so seed set up properly
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

	printf("\nTest Cases:\n");

	//test case 1:
	int test_case1[16]= {1, 4, -9, 8, 1, 3, 3, 1, -1, -4, -6, 2, 8, 19, -10, -11};
	int sizeofarray1 = sizeof(test_case1)/sizeof(int);
	struct tuple s1;
	s1=algo4(test_case1,sizeofarray1);
	print_maxsubarray(test_case1, sizeofarray1, s1);

	//test case 2:
	int test_case2[15]= {2, 9, 8, 6, 5, -11, 9, -11, 7, 5, -1, -8, -3,7, -2};
	int sizeofarray2 = sizeof(test_case2)/sizeof(int);
	struct tuple s2;
	s2=algo4(test_case2,sizeofarray2);
	print_maxsubarray(test_case2, sizeofarray2, s2);


	//test case 3:
	int test_case3[12]= {10, -11, -1, -9, 33,-45, 23,24, -1, -7, -8, 19 };
	int sizeofarray3 = sizeof(test_case3)/sizeof(int);
	struct tuple s3;
	s3=algo4(test_case3,sizeofarray3);
	print_maxsubarray(test_case3, sizeofarray3, s3);

	//test case 4:
	int test_case4[10]= {31,-41, 59, 26, -53, 58, 97, -93, -23, 84 };
	int sizeofarray4 = sizeof(test_case4)/sizeof(int);
	struct tuple s4;
	s4=algo4(test_case4,sizeofarray4);
	print_maxsubarray(test_case4, sizeofarray4, s4);


	//test case 5:
	int test_case5[9]= {3,2, 1,1,-8, 1,1,2, 3};
	int sizeofarray5 = sizeof(test_case5)/sizeof(int);
	struct tuple s5;
	s5=algo4(test_case5,sizeofarray5);
	print_maxsubarray(test_case5, sizeofarray5, s5);


	//test case 6:
	int test_case6[10]= {12, 99, 99, -99, -27, 0, 0, 0, -3,10 };
	int sizeofarray6 = sizeof(test_case6)/sizeof(int);
	struct tuple s6;
	s6=algo4(test_case6,sizeofarray6);
	print_maxsubarray(test_case6, sizeofarray6, s6);

	//test case 7:
	int test_case7[10]= {12, 99, 99, -99, -27, 0, 0, 0, -3,10 };
	int sizeofarray7 = sizeof(test_case7)/sizeof(int);
	struct tuple s7;
	s7=algo4(test_case7,sizeofarray7);
	print_maxsubarray(test_case7, sizeofarray7, s7);


	//test case 8:
	int test_case8[9]= {-2, 1,-3, 4, -1,2, 1,-5, 4};
	int sizeofarray8 = sizeof(test_case8)/sizeof(int);
	struct tuple s8;
	s8=algo4(test_case8,sizeofarray8);
	print_maxsubarray(test_case8, sizeofarray8, s8);

	//test case 9:
	int test_case9[4]= {-1.3, 2.77, -2, 12.8 };
	int sizeofarray9 = sizeof(test_case9)/sizeof(int);
	struct tuple s9;
	s9=algo4(test_case9,sizeofarray9);
	print_maxsubarray(test_case9, sizeofarray9, s9);

	//test case 10:
	int test_case10[3]= {-1, -3,-5};
	int sizeofarray10 = sizeof(test_case10)/sizeof(int);
	struct tuple s10;
	s10=algo4(test_case10,sizeofarray10);
	print_maxsubarray(test_case10, sizeofarray10, s10);

	for (k=0; k<10; k++)
	{
		int t=0;
		int array[sizeofarray];
		printf("%d. ", (k+1));
		while (t<sizeofarray)
		{
			array[t]= random_number(-100,100);
			t++;
		}
		start = clock();
		s= algo4(array,sizeofarray);
		end = clock();
		double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC*1000;
		printf("Algorithm 4: %.2f milliseconds", cpu_time_used);		        
		print_maxsubarray(array, sizeofarray, s);

	}
}

void print_maxsubarray(int *test_array, int sizeofarray, struct tuple t)
{
	int m, i, j;
	m=0;
	printf("\nOriginal Array : ");
	while (m<sizeofarray)
	{
		printf("%d", test_array[m]);
		if (m!=(sizeofarray-1))
			printf(",");
		m++;
	}
	printf("\nSubarray ");
	i = t.lowIndex;
	j = t.highIndex;
	if(i == 0 && t.sum==0)
	{
		printf(" (empty)\nMax sum: 0\n\n");
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
		printf("\nMax sum: %d\n\n", t.sum);
	}

}

struct tuple algo4(int *test_array, int sizeofarray)
{
	struct tuple d;
	assert (sizeofarray != 0);
	int max_ending_here;
	int max_start = 0; 
	int current_max;
	int endpoint;
	current_max = max_ending_here = 0;
	int i;
	int current_start=0;
	for (i=0; i< sizeofarray; i++)
	{
		if(max_ending_here<0)
		{	max_ending_here = 0;
			current_start=i;
		}
		max_ending_here = max_ending_here + test_array[i];
		
		if (current_max < max_ending_here)
		{	current_max = max_ending_here;
			max_start = current_start;
			endpoint = i;	
		}
	}
	
	d.lowIndex=max_start;
	d.highIndex=endpoint;
	d.sum=current_max;

	return d;

}		

