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


/*struct maxsubarray 
{
	int start_index;
	int end_index;
	int sum_array;
}*/

struct tuple {
     int lowIndex;
     int highIndex;
     int sum;
};


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

	//test case 1:
	int test_case1[16]= {1, 4, -9, 8, 1, 3, 3, 1, -1, -4, -6, 2, 8, 19, -10, -11};
	int sizeofarray1 = sizeof(test_case1)/sizeof(int);
	struct tuple s1;
	s1=algo4(test_case1,sizeofarray1);
	printf("\n%d %d %d\n\n", s1.lowIndex, s1.highIndex,s1.sum);

	//test case 2:
	int test_case2[15]= {2, 9, 8, 6, 5, -11, 9, -11, 7, 5, -1, -8, -3,7 -2};
	int sizeofarray2 = sizeof(test_case2)/sizeof(int);
	struct tuple s2;
	s2=algo4(test_case2,sizeofarray2);
	printf("\n%d %d %d\n\n", s2.lowIndex, s2.highIndex,s2.sum);

	//test case 3:
	int test_case3[12]= {10, -11, -1, -9, 33,-45, 23,24, -1, -7, -8, 19 };
	int sizeofarray3 = sizeof(test_case3)/sizeof(int);
	struct tuple s3;
	s3=algo4(test_case3,sizeofarray3);
	printf("\n%d %d %d\n\n", s3.lowIndex, s3.highIndex,s3.sum);

	//test case 4:
	int test_case4[10]= {31,-41, 59, 26, -53, 58, 97, -93, -23, 84 };
	int sizeofarray4 = sizeof(test_case4)/sizeof(int);
	struct tuple s4;
	s4=algo4(test_case4,sizeofarray4);
	printf("\n%d %d %d\n\n", s4.lowIndex, s4.highIndex,s4.sum);

	//test case 5:
	int test_case5[9]= {3,2, 1,1,-8, 1,1,2, 3};
	int sizeofarray5 = sizeof(test_case5)/sizeof(int);
	struct tuple s5;
	s5=algo4(test_case5,sizeofarray5);
	printf("\n%d %d %d\n\n", s5.lowIndex, s5.highIndex,s5.sum);

	//test case 6:
	int test_case6[10]= {12, 99, 99, -99, -27, 0, 0, 0, -3,10 };
	int sizeofarray6 = sizeof(test_case6)/sizeof(int);
	struct tuple s6;
	s6=algo4(test_case6,sizeofarray6);
	printf("\n%d %d %d\n\n", s6.lowIndex, s6.highIndex,s6.sum);

	//test case 7:
	int test_case7[10]= {12, 99, 99, -99, -27, 0, 0, 0, -3,10 };
	int sizeofarray7 = sizeof(test_case7)/sizeof(int);
	struct tuple s7;
	s7=algo4(test_case7,sizeofarray7);
	printf("\n%d %d %d\n\n", s7.lowIndex, s7.highIndex,s7.sum);

	//test case 8:
	int test_case8[9]= {-2, 1,-3, 4, -1,2, 1,-5, 4};
	int sizeofarray8 = sizeof(test_case8)/sizeof(int);
	struct tuple s8;
	s8=algo4(test_case8,sizeofarray8);
	printf("\n%d %d %d\n\n", s8.lowIndex, s8.highIndex,s8.sum);

	//test case 9:
	int test_case9[4]= {-1.3, 2.77, -2, 12.8 };
	int sizeofarray9 = sizeof(test_case9)/sizeof(int);
	struct tuple s9;
	s9=algo4(test_case1,sizeofarray9);
	printf("\n%d %d %d\n\n", s9.lowIndex, s9.highIndex,s9.sum);

	//test case 10:
	int test_case10[3]= {-1, -3,-5};
	int sizeofarray10 = sizeof(test_case10)/sizeof(int);
	struct tuple s10;
	s10=algo4(test_case10,sizeofarray10);
	printf("\n%d %d %d\n\n", s10.lowIndex, s10.highIndex,s10.sum);


	for (k=0; k<10; k++)
	{
		int t=0;
		int array[sizeofarray];
		printf("%d. ", (k+1));
		printf("[");
		while (t<sizeofarray)
		{
			array[t]= random_number(-100,100);
			printf("%d", array[t]);
			if (t!=(sizeofarray-1))
			printf(",");
			t++;
		}
		printf("], ");
		start = clock();
		s= algo4(array,sizeofarray);
		end = clock();
		double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC*1000;
		//printf("\nAlgo took: %f milliseconds.\n", cpu_time_used);		        
		printf("\n%d %d %d\n\n", s.lowIndex, s.highIndex,s.sum);
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
//	d.sum=max_ending_here;	
	d.sum=current_max;

	//Print functionality for max sum and max array

	if (current_max != 0)
	{
		printf("[");
		for(int m=max_start;m<=endpoint;m++)
		{
			printf("%d", test_array[m]);
			if(m<endpoint)
				printf(",");				
		}
		printf("],");
//		printf("%d", max_ending_here);
		printf("%d", current_max);


	}


	else printf("The array had only numbers <= 0");

	return d;

}		

