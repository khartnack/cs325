/*
	Kathleen Beltramini
	beltramk@onid.oregonstate.edu
	CS325-400
	Project 1
*/

#include <stdio.h> 
#include <stdlib.h>


int algo4(int *test_array, int sizeofarray);


//Takes in the arguments from the command lines and provides parameters to functions
int main(int argc, char **argv) 
{
	int array[14]= {2, 3, -2, 1, 4, -5, 2, 3, 1, -2, 10, -4, 1, 2};
	int sizeofarray = sizeof(array)/sizeof(int);
	int maxsum;
	maxsum=algo4(array,sizeofarray);
	printf("\nmax sum of array: %d\n", maxsum);
}


int algo4(int *test_array, int sizeofarray)
{
	int max_ending_here, current_max = 0;
	for (int i=0; i< sizeofarray; i++)
	{
		max_ending_here = max_ending_here + test_array[i];
		if(max_ending_here<0)
			max_ending_here = 0;
		if (current_max < max_ending_here)
			current_max = max_ending_here;
	}
	return current_max;
}

