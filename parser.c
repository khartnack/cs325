/*
David Crisman
Garrett Genz
Kathleen Beltramini
Project Group 6
CS325 - W2015
*/


#include <stdio.h> 
#include <stdlib.h>


//reference: http://cboard.cprogramming.com/c-programming/63552-read-numbers-file.html

int main(int argc, char **argv)
{
        char c;
	char ch;
	int data;
	int change;
        FILE *fp;
	char *filename = argv[1];
	char array[1000];
	char coin_array[1];
	int count = 0;

        if((fp=fopen(filename,"r"))==NULL)
        {
                printf("cannot open the file");
                exit(1);
	}
    	else

	{
		while(EOF!=(c=fgetc(fp))){
    		{
			if (c=='[')
			{
				while(ch!=']')
				{
					fscanf(fp,"%d%c", &data, &ch);
				        array[count++] = data;							
				}
				int k;		
	
				for(k=0; k<count; k++)    
				{
					printf("%d ", array[k]);
				}
				count = 0;	
 			}
			else
			{
				fscanf(fp,"%d%c", &change, &ch);
				coin_array[0] = change;
				printf("\n%d\n",coin_array[0]);

			}

			}
		}

	}
}
