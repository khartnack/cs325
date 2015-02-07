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
        FILE *fp;
	char *filename = argv[1];
         
        if((fp=fopen(filename,"r"))==NULL)
        {
                printf("cannot open the file");
                exit(1);
	}
    	
 	else
	{
   		while(c!=EOF)
    		{
       			c=fgetc(fp);
			if((c >= '0' && c <= '9') ||  (c == ',') || (c == '[') || (c == ']') || (c == '\n'))
	       			 printf("%c",c);    		}   
		}

//	close(filename);
}
