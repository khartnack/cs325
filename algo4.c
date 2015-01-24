#include <stdio.h> 
#include <stdlib.h>


int algo4(int *test_array, int sizeofarray);


//Takes in the arguments from the command lines and provides parameters to functions
int main(int argc, char **argv) 
{
	
	int array[8]= {-2, -3, 4, -1, -2, 1, 5, -3};
	int sizeofarray = sizeof(array)/sizeof(int);
	int maxsum;
	maxsum=algo4(array,sizeofarray);
	printf("\nmax sum of array: %d\n", maxsum);
}


int algo4(int *test_array, int sizeofarray)
{
	int max_ending_here;
	int current_max;
	max_ending_here = current_max = 0;
	int i=0;
	while(i<sizeofarray)
	{
		max_ending_here = max_ending_here + test_array[i];
		if(max_ending_here<0)
			max_ending_here = 0;
		if (current_max < max_ending_here)
			current_max = max_ending_here;
		i++;
	}
	return current_max;

}
