/*
David Crisman
Garrett Genz
Kathleen Beltramini
CS325 - W2015
Project Group 6
Project 4
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

struct city {
	int city_id;
	int x;
	int y;
}city_array[100000];



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
	struct city new_city;
	struct timeval start, end, result;
	//char c; //used to get characters out of input file
	//char ch; //holds comma
	FILE *fp; //input file that is opened to read
	FILE *outfp;  //holds output file that is opened to write to
	char *filename = argv[1];  //holds input file name provided by command line
	char outfilename[255];  //holds output file that is created by filenamechange.txt
	int len = strlen(filename);  //length of filename
	int m;
	//int data = 0;
	int count = 0;
	int k=0;
	//int city_array[100000];
	//changes the outfile name so that it has filenamechange.txt
	for(m=0; m<(len); m++)
	{
		outfilename[m]=filename[m];
	}
	outfilename[m++]='.';
	outfilename[m++]='t';
	outfilename[m++]='o';
	outfilename[m++]='u';
	outfilename[m++]='r';
	while(m<=255)
	{
		outfilename[m]=0;
		m++;
	}

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
		while(fscanf(fp,"%d %d %d", &new_city.city_id, &new_city.x, &new_city.y)==3)
		{
			city_array[k].city_id=new_city.city_id;
			city_array[k].x=new_city.x;
			city_array[k].y=new_city.y;
			k++;
			count++;
			gettimeofday(&start, NULL);  //times the algorithm
			//sleep(1);
			gettimeofday(&end, NULL);  //stops the time clock for algorithm 
			timeval_subtract(&result, &end, &start);  //measures the difference in time
			//printf(" %ld.%06ld\n",result.tv_sec, result.tv_usec);  //prints to screen the time results

		}
		for(k=0;k<count; k++)	
		{
		    printf("%d %d %d\n", city_array[k].city_id, city_array[k].x, city_array[k].y);
		    fprintf(outfp, "%d %d %d\n", city_array[k].city_id, city_array[k].x, city_array[k].y);
		}	

	}

}
