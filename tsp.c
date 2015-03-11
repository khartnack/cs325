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
	int noChange = 0;
	int best_dist = total_dist;
	int new_dist = 0; 
	int new_total_dist = 0;
	int new_tour[m];
	int best_tour[m];
	int swap=0;
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
			for(int p=0; p+1<m; p++)
			{
				printf("new tour: %d\n", new_tour[p]);
				w= new_tour[p];
				z= new_tour[p+1];
				new_dist=calc_distance(city_array[w].x, city_array[w].y, city_array[z].x, city_array[z].y);
				new_total_dist = new_total_dist + new_dist;
			}
			printf("new total dist : %d\n", new_total_dist);
			
			if(new_total_dist<best_dist)
			{
				best_dist = new_total_dist;
				for(int p=0; p<m; p++)
				{
					best_tour[p]=new_tour[p];
					printf("best_tour: %d\n", best_tour[p]);
				}
				printf("\n");
			}	
			
			//new_dist=calc_distance(city_array[w].x, city_array[w].y, city_array[z].x, city_array[z].y);
			printf("w z new dist: %d %d %d\n", w, z, best_dist);
		}
		

	}
	/*
	for(i=0; i<m; i++)
	{
		printf("city tour: %d\t%d\n", city_tour[i], new_tour[i]);

	}*/

	for(k=0;k<n; k++)	
	{
		for (j=0; j<m; j++)
		{
			printf("%d\t", dist_matrix[k][j]);
			if(j==(m-1))
				printf("\n");
		}
	}
	return 0;
}

/*  Pseudo code for 2 opt
    1.   T = some starting tour
    2.   noChange = true
    3.   repeat
    4.      for all possible edge-pairs in T
    5.         T' = tour by swapping end points in edge-pair
    6.         if T' < T
    7.             T = T'
    8.             noChange = false
    9.             break      // Quit loop as soon as an improvement is found
    10.        endif
    11.     endfor
    12.  until noChange
    13.  return T
*/

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
	//int n;
	//int m;
	struct city new_city;
	struct timeval start, end, result;
	//char c; //used to get characters out of input file
	//char ch; //holds comma
	FILE *fp; //input file that is opened to read
	FILE *outfp;  //holds output file that is opened to write to
	char *filename = argv[1];  //holds input file name provided by command line
	char outfilename[255];  //holds output file that is created by filenamechange.txt
	int len = strlen(filename);  //length of filename
	int z;
	//int data = 0;
	int count = 0;
	int k=0;
	int city_dist;
	static int dist_between[7][7];
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
	gettimeofday(&start, NULL);  //times the algorithm
	int j;
	for(k=0;k<count; k++)	
	{
		for (j=0; j<count; j++)
		{
			city_dist=calc_distance(city_array[k].x, city_array[k].y, city_array[j].x, city_array[j].y);
			dist_between[k][j]=city_dist;
			if(k==0)
			{
				total_dist = total_dist + city_dist;
			}
		}
	}

	j=count;
	k=count;
	two_opt(solution, j, k,total_dist, dist_between);

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





