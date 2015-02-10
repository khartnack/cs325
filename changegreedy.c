/*
David Crisman
Garrett Genz
Kathleen Beltramini
CS325 - W2015
Project Group 6
Project 2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* memset */
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <dirent.h>
#include <math.h>     
#include <limits.h>

//reference: http://cboard.cprogramming.com/c-programming/63552-read-numbers-file.html
//http://stackoverflow.com/questions/6074279/how-to-use-fprintf-for-writing-data-to-a-file
//http://stackoverflow.com/questions/10709804/read-comma-separated-numbers-from-a-file-in-c

void timeval_subtract (result, x, y)
     struct timeval *result, *x, *y;
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }

  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;
}


int main(int argc, char **argv)
{
	struct timeval start, end, result;
	char c; //used to get characters out of input file
	char ch; //holds comma
	int data = 0; //will hold coin type values
	int change; //holds change required to change from input file
	FILE *fp; //input file that is opened to read
	FILE *outfp;  //holds output file that is opened to write to
	char *filename = argv[1];  //holds input file name provided by command line
	char outfilename[255];  //holds output file that is created by filenamechange.txt
	int len = strlen(filename);  //length of filename
	int m;
	//changes the outfile name so that it has filenamechange.txt
	for(m=0; m<(len-4); m++)
	{
		outfilename[m]=filename[m];
	}

	outfilename[m++]='c';
	outfilename[m++]='h';
	outfilename[m++]='a';
	outfilename[m++]='n';
	outfilename[m++]='g';
	outfilename[m++]='e';
	outfilename[m++]='.';
	outfilename[m++]='t';
	outfilename[m++]='x';
	outfilename[m++]='t';
	while(m<=255)
	{
		outfilename[m]=0;
		m++;
	}
	int array[1000];  //assumes no more than 1000 coins
	int count = 0;
	int chamt; //holds change amount left to calculate
	int array_size;
	int i = 0;
	int run_total=0;  //holds running total of the sum of coins to use for change
	int array2[1000]; //assumes no more than 1000 coins

	if((outfp=fopen(outfilename,"w"))==NULL)
	{
		printf("cannot open the file");
		exit(1);
	}

	if((fp=fopen(filename,"r"))==NULL)
	{
		printf("cannot open the file");
		exit(1);
	}
	
	else
	{
		while(EOF!=(c=fgetc(fp)))  //reads in the file to parse the array of coins and change required
		{
			if (c=='[') 
			{
				while(ch!=']')
				{
					fscanf(fp,"%d%c", &data, &ch);  //scans in the array of coin values
					array[count++] = data;  //array[count] holds the array of change to use to calculate change
				}
				array_size = count;  //holds the size of the array with coins & will increase as values read in
				count = 0;  //resets count to 0 for when multiple arrays in file
			}
			else
			{
				fscanf(fp,"%d%c", &change, &ch);  //reads in the value of the change to be calculated
				chamt = change;   //sets chamt to change for use in the algorithms

			//Greedy Algorithm starts here 
				gettimeofday(&start, NULL);  //times the algorithm
			
				int coin_count; 
				for(i=(array_size-1); i>=0; i--)  //goes through the array of coins starting with the largest size 
				{
					coin_count=0;
					array2[i]=0;
					while((array[i]<=chamt)&&(chamt>0)&& array_size>0)
					{
						chamt = chamt - array[i];
						coin_count++;
						array2[i]=coin_count;
					}

				run_total = run_total + coin_count; //holds the number of coins
				}

			gettimeofday(&end, NULL);  //stops the time clock for algorithm 
			timeval_subtract(&result, &end, &start);  //measures the difference in time
			printf("%d, %ld.%06ld\n",change, result.tv_sec, result.tv_usec);  //prints to screen the time results

//Prints to file the array with totals per coin and the minimum # of coins
//The coins coints are stored in array2
//The min # of coins is in run_total

			fprintf(outfp, "[");

			for(i=0;i<array_size;i++)
			{
				if(i<(array_size - 1))
					fprintf(outfp,"%d,", array2[i]);
				else
					fprintf(outfp,"%d", array2[i]);
			}

			fprintf(outfp,"]\n");
			fprintf(outfp,"%d\n", run_total);
			run_total = 0; //resets in case multiple arrays in file
			}
		}
	}
}
