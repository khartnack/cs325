/*
	Kathleen Beltramini
	beltramk@onid.oregonstate.edu
	CS325-400
	Project 1
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> /* memset */

void algo4(int *test_array, int sizeofarray);

//Takes in the arguments from the command lines and provides parameters to functions
int main(int argc, char **argv) 
{
	//need to use malloc?
	//int array[15]= {2,-4,3,-2,1,4,-5,2,3,1,-2,10,-4,1,2};
	int array[10]= {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
	int sizeofarray = sizeof(array)/sizeof(int);
	algo4(array,sizeofarray);
}

void algo4(int *test_array, int sizeofarray)
{
	int max_ending_here = 0; 
	int current_max = 0;
	int endpoint, endpoint2;
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
	printf("The maximum sum is: %d\n", current_max);

	printf("The maximum subarray is:\n");
				
	//tried to come up with a way to handle counting, will need to verify that it works
	printf("Count Method:\n");
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

