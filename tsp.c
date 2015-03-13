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


struct city {
	int city_id;
	int x;
	int y;
}city_array[20000];

static FILE *outfp;


void MST(struct city *city_array, int *tour, int n, int **dist_matrix);

//calculates the distance between any two cities.  
//input is city 1's x coordinate, city 1's y coordinate, city 2's x coordinate, city 2's y coordinate
//the distance between the 2 points is returned
int calc_distance(int ax, int ay, int bx, int by)
{
	int dist;
	dist =  round(sqrt((ax-bx)*(ax - bx) + (ay - by)*(ay-by)));
	return dist;
}

//references for 2 opt implementation
//http://en.wikipedia.org/wiki/2-opt
//http://www.technical-recipes.com/2012/applying-c-implementations-of-2-opt-to-travelling-salesman-problems/
//http://www.seas.gwu.edu/~simhaweb/champalg/tsp/tsp.html  reference for 2-OPT implementation
//Function performs a 2 opt optimization of a tour
//Inputs are the existing tour, # of columns in dist_matrix, # of rows in dist_matrix, the total distance of existing tour, and a 2D 
//array holding all of the distances between the 2 cities
void *two_opt(int *city_tour,  int m, int n,   int total_dist, int **dist_matrix)
{
	int i=0;
	int k=0;
	int w=0;
	int z=0;
	int best_dist = total_dist;  //initial distance of tour becomes the current best tour distance
	int new_dist = 0;  //holds distance between 2 cities
	int new_total_dist = 0;  //holds a new distance of tour resulting from swap in 2 opt
	int new_tour[m]; //array holding the current tour from the 2-opt swap
	for(i=0;i<m-1; i++)	
	{
		for (k=i+1; k<m; k++)
		{
			//2 opt swap 
			int c;
			for(c=0; c<=(i-1); ++c)
			{
				new_tour[c]=city_tour[c];		
			}
			//where the swap occurs
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
			//calculates the distance of the new tour with the swap
			for(int p=0; p<m; p++)  
			{
				w= new_tour[p];
				if(p==(m-1))
					z=new_tour[0];
				else
					z= new_tour[p+1];	
				new_dist=dist_matrix[w][z];
				new_total_dist = new_total_dist + new_dist;
			}
			//if the swap is better, then the new tour becomes the more optimal tour
			if(new_total_dist<best_dist)
				{
					best_dist = new_total_dist;
					for(int p=0; p<m; p++)
					{
						city_tour[p]=new_tour[p];  //tried memcpy, but saw no improvement on 2k
					}
				
				}			
		}
	}
	//prints the result of the optimization to the filename.tour file
	fprintf(outfp,"%d\n", best_dist);
	for(int p=0; p<m; p++)
	{
		fprintf(outfp,"%d\n", city_tour[p]);
	}
	return 0;
}

// From http://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html
// Used to substract two timeval structs
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
	char *filename = argv[1];  //holds input file name provided by command line
	char outfilename[255];  //holds output file that is created by filenamechange.txt
	int len = strlen(filename);  //length of filename
	int z;
	int count = 0;
	int k=0;
	int total_dist = 0;
	int solution[20000];
	//changes the outfile name so that it has filename.txt.tour
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
		 //copies the input file data into an array
		while(fscanf(fp,"%d %d %d", &new_city.city_id, &new_city.x, &new_city.y)==3) 
		{
			city_array[k].city_id=new_city.city_id;
			city_array[k].x=new_city.x;
			city_array[k].y=new_city.y;
			k++;
			count++;			
		}
		//just for now, to verify that array is storing data correctly


	}
	
	int j;
	int *distance[count];
	for (k=0; k<count; k++)
         	distance[k] = (int *)malloc(count * sizeof(int));

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

	j=count;
	k=count;
	MST(city_array, solution, count, distance);
	int m=count;
	/*for(int p=0; p<m; p++)
	{
		printf("%d\n", solution[p]);
	}*/
	int w;
	int q;

	int city_dist;
	for(int p=0; p<m; p++)  
	{
		w= solution[p];
		if(p==(m-1))
			q=solution[0];
		else
			q= solution[p+1];	
		city_dist=distance[w][q];
		total_dist = total_dist + city_dist;
	}
	two_opt(solution, j, k,total_dist, distance);  //calls 2-OPT algo
	gettimeofday(&end, NULL);  //stops the time clock for algorithm 
	timeval_subtract(&result, &end, &start);  //measures the difference in time
	printf(" %ld.%06ld\n",result.tv_sec, result.tv_usec);  //prints to screen the time results
	
}

void MST(struct city *city_array, int *tour, int n, int **dist_matrix){

 	int i,j,e = 1,minT = 0,a,b,min = INT_MAX;

 	int visited[n];
	for(j=0; j<n; j++)
	{
		visited[j]=0;
	}
 	visited[0] = 1;
 	tour[0] = city_array[0].city_id;
 	while(e < n)
	{
      	for(i = 0, min = INT_MAX; i < n; ++i)
		{
           		if(visited[i] == 1)
			{
                		for(j = 0; j < n; ++j)
				{
          	           		if(visited[j] != 1){
                          			if(dist_matrix[i][j] < min)
						{
                               				min = dist_matrix[i][j];
                               				a = i;
                               				b = j;
        	                  		}
                     		}
                	}
           	}

      	}
      	tour[e] = city_array[b].city_id;
      	minT += min;
      	e++;
      	visited[b] = 1;
 	}
 	return;
}








