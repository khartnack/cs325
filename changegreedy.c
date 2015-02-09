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
	char c;
	char ch;
	int data = 0;
	int change;
	FILE *fp;
	FILE *outfp;
	char *filename = argv[1];
	char outfilename[255];
	int len = strlen(filename);
	int m;
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
	int array[1000];
	int coin_array[1];
	int count = 0;
	int chamt;
	int array_size;
	int i = 0;
	int run_total=0;
	int array2[1000];

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
		while(EOF!=(c=fgetc(fp)))
		{
			if (c=='[')
			{
				while(ch!=']')
				{
					fscanf(fp,"%d%c", &data, &ch);
					array[count++] = data;
					//array[count] holds the array of change to use to calculate change
				}
				array_size = count;
				count = 0;
			}
			else
			{
				fscanf(fp,"%d%c", &change, &ch);
				coin_array[0] = change;   //HOLDS THE # TO CALCULATE CHANGE
				chamt = change;

			//Greedy Algorithm starts here 
				gettimeofday(&start, NULL);
			
				int coin_count; 
				for(i=(array_size-1); i>=0; i--) 
				{
					coin_count=0;
					array2[i]=0;
					while((array[i]<=chamt)&&(chamt>0)&& array_size>0)
					{
						chamt = chamt - array[i];
						coin_count++;
						array2[i]=coin_count;
					}

				run_total = run_total + coin_count;
				}

			gettimeofday(&end, NULL);
			timeval_subtract(&result, &end, &start);
			printf("%d, %ld.%06ld\n",change, result.tv_sec, result.tv_usec);

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
			run_total = 0;		 
			}
		}
	}
}
