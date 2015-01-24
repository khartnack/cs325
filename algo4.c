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


void algo4(int *test_array, int sizeofarray);

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


int main(int argc, char **argv) 
{
	srand(time(NULL));
	int sizeofarray;
	char size_string[10];
	strcpy(size_string,argv[1]); 
	//printf("%s",size_string);
	sizeofarray=atoi(size_string);
	//char * stringarray;
	int array[sizeofarray];
	int t=0;
	while (t<sizeofarray)
	{
		array[t]= random_number(-100,100);
		printf("%d ", array[t]);
		t++;
	}
	//need to use malloc?
	//int array[15]= {2,-4,3,-2,1,4,-5,2,3,1,-2,10,-4,1,2};
	//int array[10]= {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
	//int sizeofarray = sizeof(array)/sizeof(int);
	//sprintf(stringarray,array);
	algo4(array,sizeofarray);
}

void algo4(int *test_array, int sizeofarray)
{
	assert (sizeofarray != 0);
	int max_ending_here = 0; 
	int current_max = 0;
	int endpoint=0;
	int  endpoint2=0;
	int sum;
	int i;
	int count=0;
	for (i=0; i< sizeofarray; i++)
	{
		max_ending_here = max_ending_here + test_array[i];
		if(max_ending_here<0)
		{	max_ending_here = 0;
			count = 0;
		}
		else count++;
		if (current_max < max_ending_here)
		{	current_max = max_ending_here;
			endpoint = endpoint2 = i;	
			//endpoint2 = i;
		}
	}
		if(endpoint<i)
		{
			count=count-(i-endpoint);
		}	

	//Print functionality for max sum and max array
	printf("\nThe maximum sum is: %d\n", current_max);

	printf("The maximum subarray is:\n");
				
	//tried to come up with a way to handle counting, will need to verify that it works
	printf("Count Method: NOT WORKING CONSISTENTLY FOR LARGE ARRAYS\n");

	if (current_max != 0)
	{
	while(count>=0)
	{
		printf("%d ", test_array[endpoint-count]);	
		count--;
	}
	printf("\n");


	printf("Iterating backwards summing elements:\n");
	sum=test_array[endpoint];

	//calculates from max sum back to get the elements in the array
	//could have also created a separate array to track the subarray
	//so did not have to iterate backwards 

	while(sum<current_max)
	{
		endpoint=endpoint-1;
		sum = test_array[endpoint]+sum;
	}

	//once reaches the start of the subarray, moves forward to
	//display the subarray in order
	while(endpoint2>=endpoint)
	{
		printf("%d ",test_array[endpoint]);
		endpoint++;
	}
	}
	else printf("The array had only numbers <= 0");
	
}		

