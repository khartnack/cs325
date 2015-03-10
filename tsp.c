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

int calc_distance(int ax, int ay, int bx, int by);

void *two_opt(void *dist_matrix, int *city_tour, int num_cities);

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
	int city_dist;
	static int dist_between[20000][20000];
/*	int x, y;
	for(x = 0; x < 1500; x++) 
	{
    		for(y = 0; y < 1500; y++) 
		{	
			dist_between[x][y] = 0;
		}
	}*/
	int total_dist = 0;
	int solution[10000];

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
		}
		//just for now, to verify that array is storing data correctly
		for(k=0;k<count; k++)	
		{
		    solution[k]=k;
		    printf("%d %d %d\n", city_array[k].city_id, city_array[k].x, city_array[k].y);
		}	

	}
	gettimeofday(&start, NULL);  //times the algorithm
	int j;
	for(k=0;k<count; k++)	
	{
		for (j=0; j<count; j++)
		{
			city_dist=calc_distance(city_array[k].x, city_array[k].y, city_array[j].x, city_array[j].y);
			dist_between[j][k]=city_dist;
			printf("%d\t", dist_between[j][k]);
			if(j==(count-1))
			{
				printf("\n");
			}
			//total_dist = total_dist + city_dist;
		}
	}
	two_opt(dist_between, solution, count);
	gettimeofday(&end, NULL);  //stops the time clock for algorithm 
	timeval_subtract(&result, &end, &start);  //measures the difference in time
	//printf(" %ld.%06ld\n",result.tv_sec, result.tv_usec);  //prints to screen the time results
	printf("%d\n", total_dist);
	fprintf(outfp, "%d\n", total_dist);
	for(k=0;k<count; k++)	
		{
		    fprintf(outfp, "%d\n", k);
		}

}

int calc_distance(int ax, int ay, int bx, int by)
{
	int dist;
	dist =  sqrt((ax-bx)*(ax - bx) + (ay - by)*(ay-by));
	return dist;
}


//http://www.seas.gwu.edu/~simhaweb/champalg/tsp/tsp.html  reference for 2-OPT implementation
void *two_opt(void *dist_matrix, int *city_tour, int num_cities)
{
	printf("test");
	return 0;
}
