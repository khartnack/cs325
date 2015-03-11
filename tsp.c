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
}city_array[2000];

static FILE *outfp;

int calc_distance(int ax, int ay, int bx, int by);
//	two_opt(solution, j, k,total_dist, dist_between);
//http://www.seas.gwu.edu/~simhaweb/champalg/tsp/tsp.html  reference for 2-OPT implementation
void *two_opt(int *city_tour,  int m, int n,   int total_dist, int dist_matrix[n][m])
{
	int i=0;
	int k=0;
	int j=0;
	int w=0;
	int z=0;
	//int noChange = 0;
	int best_dist = total_dist;
	int new_dist = 0; 
	int new_total_dist = 0;
	int new_tour[m];
	int best_tour[m];
	//int swap=0;
	for(i=0;i<m-1; i++)	
	{
		for (k=i+1; k<m; k++)
		{
			int c;
			for(c=0; c<=(i-1); ++c)
			{
				new_tour[c]=city_tour[c];		
			}
			int rev = 0;
			for(c = i; c <= k; ++c)
			{
				new_tour[c]=city_tour[k-rev];
				rev++;
			}
			for (c=(k+1); c< m; ++c)
			{
				new_tour[c]=city_tour[c];
			}
			w=0;
			new_total_dist = 0;
			for(int p=0; p<m; p++)  //should it be p+1
			{
				w= new_tour[p];
				
				if(p==(m-1))
					z=new_tour[0];
				else
					z= new_tour[p+1];	
				new_dist=calc_distance(city_array[w].x, city_array[w].y, city_array[z].x, city_array[z].y);
				new_total_dist = new_total_dist + new_dist;
			}
			
			if(new_total_dist<best_dist)
			{
				best_dist = new_total_dist;
				//fprintf(outfp,"%d\n", best_dist);
				for(int p=0; p<m; p++)
				{
					best_tour[p]=new_tour[p];
					//fprintf(outfp,"%d\n", best_tour[p]);
				}
				
			}	
			
		}
		

	}
	fprintf(outfp,"%d\n", best_dist);
	for(int p=0; p<m; p++)
	{
		fprintf(outfp,"%d\n", best_tour[p]);
	}


	/*printf("\nMatrix: for Debugging\n");
	for(k=0;k<n; k++)	
	{
		for (j=0; j<m; j++)
		{
			printf("%d\t", dist_matrix[k][j]);
			if(j==(m-1))
				printf("\n");
		}
	}*/
	return 0;
}


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
	gettimeofday(&start, NULL);  //times the algorithm
	struct city new_city;
	FILE *fp; //input file that is opened to read
	//FILE *outfp;  //holds output file that is opened to write to
	char *filename = argv[1];  //holds input file name provided by command line
	char outfilename[255];  //holds output file that is created by filenamechange.txt
	int len = strlen(filename);  //length of filename
	int z;
	//int data = 0;
	int count = 0;
	int k=0;
	int city_dist;
	//static int dist_between[280][280];
	/*int x, y;
	for(x = 0; x < 2000; x++) 
	{
    		for(y = 0; y < 2000; y++) 
		{	
			dist_between[x][y] = 1;
		}
	}*/
	int total_dist = 0;
	int solution[2000];

	//changes the outfile name so that it has filenamechange.txt
	for(z=0; z<(len); z++)
	{
		outfilename[z]=filename[z];
	}
	outfilename[z++]='.';
	outfilename[z++]='t';
	outfilename[z++]='o';
	outfilename[z++]='u';
	outfilename[z++]='r';
	while(z<=255)
	{
		outfilename[z]=0;
		z++;
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

	int j;
	int distance[count][count];

	//Calculate the distance for half of the matrix
	for(j=0;j<count; j++)
	{
		for(k=j+1; k<count; k++)
		{
			distance[j][k] = calc_distance(city_array[j].x, city_array[j].y, city_array[k].x, city_array[k].y);
		}
		
	}

	//Copy the first half to the second half
	for(k=0;k<count; k++)
	{
		for(j=k+1; j<count; j++)
		{
			distance[j][k] = distance [k][j];
		}
		
	}

	//Set the diaganol to 0 (the distance from a vertex to itself is 0)
	for(k=0;k<count; k++)
	{
		distance[k][k] = 0;
	}
	
		
	total_dist=INT_MAX;
	
	j=count;
	k=count;
	//int *best_tour;
	two_opt(solution, j, k,total_dist, distance);
	gettimeofday(&end, NULL);  //stops the time clock for algorithm 
	timeval_subtract(&result, &end, &start);  //measures the difference in time
	printf(" %ld.%06ld\n",result.tv_sec, result.tv_usec);  //prints to screen the time results
	
}

int calc_distance(int ax, int ay, int bx, int by)
{
	int dist;
	dist =  round(sqrt((ax-bx)*(ax - bx) + (ay - by)*(ay-by)));
	return dist;
}





