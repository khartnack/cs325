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
//http://stackoverflow.com/questions/10709804/read-comma-separated-numbers-from-a-file-in-c

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
    FILE *fp;
    int data,row,col,c,count,inc;
    int *array, capacity=10;
    char ch;
    array=(int*)malloc(sizeof(int)*capacity);
    char *filename = argv[1];
    fp=fopen(filename,"r");
    row=col=c=count=0;
    while(EOF!=(inc=fscanf(fp,"%d%c", &data, &ch)) && inc == 2){
        ++c;//COLUMN count
        if(capacity==count)
            array=(int*)realloc(array, sizeof(int)*(capacity*=2));
        array[count++] = data;
	
        if(ch == '\n'){
            ++row;
            if(col == 0){
                col = c;
            //} else if(col != c){
            //    fprintf(stderr, "format error of different Column of Row at %d\n", row);
            //    goto exit;
            }
            c = 0;
      //  } else if(ch != ','){
       //     fprintf(stderr, "format error of different separator(%c) of Row at %d \n", ch, row);
        //    goto exit;
        }
    }
    {   //check print
        int i,j;
//      int (*matrix)[col]=array;
        for(i=0;i<row;++i){
            for(j=0;j<col;++j)
                printf("%d ", array[i*col + j]);//matrix[i][j]
            printf("\n");
        }
    }
exit:
    fclose(fp);
    free(array);
    return 0;
}
