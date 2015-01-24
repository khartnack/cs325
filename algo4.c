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
	int array[15]= {2,-4,3,-2,1,4,-5,2,3,1,-2,10,-4,1,2};
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
	for (i=0; i< sizeofarray; i++)
	{
		max_ending_here = max_ending_here + test_array[i];
		if(max_ending_here<0)
		{	max_ending_here = 0;
		}
		if (current_max < max_ending_here)
		{	current_max = max_ending_here;
			endpoint = i;	
			endpoint2 = i;
		}		
	}
	printf("The maximum sum is: %d\n", current_max);
	printf("The maximum subarray is: ");
	sum=test_array[endpoint];

	while(sum<current_max)
	{
		endpoint=endpoint-1;
		sum = test_array[endpoint]+sum;
	}

	while(endpoint2>=endpoint)
	{
		printf("%d ",test_array[endpoint]);
		endpoint++;
	}
	printf("\n");
	
}		

