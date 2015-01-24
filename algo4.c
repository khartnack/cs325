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
	
	int array[5]= {2,4,5,1,6};
	int sizeofarray = sizeof(array)/sizeof(int);
	int maxsum;
	maxsum=algo4(array,sizeofarray);
	printf("\nmax sum of array: %d\n", maxsum);
}


int algo4(int *test_array, int sizeofarray)
{
	int i=0;
	int sum=0;
	//int array_size = sizeofarray;
	//printf("size: %d", array_size);
	while(i<sizeofarray)
	{
		//printf("%d ", i);
		sum = sum + test_array[i];
		i++;
	}
	return sum;

}

