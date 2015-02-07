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
   		do
    		{
       			c=fgetc(fp);
       		 	if(c==' ' || c=='\n')
			        continue;
       			 printf("%c",c);
    		}while(c!=EOF);   
	}
getchar();




/*	int file_size;
	int cur_count;
	char in_fd;
	char ch;
	in_fd = open(filename, O_RDONLY);  //opens the archive
	file_size = lseek(in_fd, -1, SEEK_END) + 1; //from reverse.c program in clas
	cur_count = lseek(in_fd, 0, SEEK_SET); //go past the arch text at beginning
	void *buffer = 1024;
	while(cur_count < file_size)
	{
		read(in_fd, buffer, sizeof(file_size));
		printf("%s", buffer);

	}
	close(in_fd);*/
}
