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

