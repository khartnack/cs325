/*
David Crisman
Garrett Genz
Kathleen Beltramini
Project Group 6
CS325 - W2015
*/

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h> 
#include <getopt.h> 
#include <sys/utsname.h> 
#include <time.h> 
#include <sys/stat.h> 
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

//reference: http://cboard.cprogramming.com/c-programming/63552-read-numbers-file.html

int main(int argc, char **argv)
{
        char c;
	char ch;
	int data;
	int inc;
        FILE *fp;
	char *filename = argv[1];
	char array[10000];
	int count = 0;

        if((fp=fopen(filename,"r"))==NULL)
        {
                printf("cannot open the file");
                exit(1);
	}
    	else

	{
   		while(c!=EOF)
    		{
			int i = 0;
       			c=fgetc(fp);
			if (c=='[')
			{
				//c=fgetc(fp);
				//printf("%c, ",c);  
				while(ch!=']')
				{
					inc=fscanf(fp,"%d%c", &data, &ch);
				        array[count++] = data;			
				
			}
			}   
			if (c=='\n')   
			{
				c=fgetc(fp);
				printf("change: %c",c);
				while(c >= '0' && c <= '9')
				{
					c=fgetc(fp);
					printf("%c\n",c);
				}
				i=0;
			}

		}
	while(count>0)
	{
		printf("%d", array[count-1]);
		count--;
	}
	}

}
