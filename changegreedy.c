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
	int chamt;
	int array_size;
	int i = 0;
	int run_total=0;
	char array2[1000];
	if((fp=fopen(filename,"r"))==NULL)
	{
		printf("cannot open the file");
		exit(1);
	}
	
	else
	{
	while(EOF!=(c=fgetc(fp)))
	{
		if (c=='[')
		{
			while(ch!=']')
			{
				fscanf(fp,"%d%c", &data, &ch);
				array[count++] = data;
			}
			array_size = count;
			count = 0;
		}
		else
		{
			fscanf(fp,"%d%c", &change, &ch);
			coin_array[0] = change;
		//}
		chamt = coin_array[0];
		int coin_count;
		for(i=(array_size-1); i>=0; i--)
		{
			coin_count=0;
			while((array[i]<=chamt)&&(chamt>0)&& array_size>0)
			{
				chamt = chamt - array[i];
				coin_count++;
				array2[i]=coin_count;
			}
			run_total = run_total + coin_count;
		}

		printf("[");
		for(i=0;i<array_size;i++)
		{
			if(i<(array_size - 1))
				printf("%d,", array2[i]);
			else
				printf("%d", array2[i]);
		}

		printf("]\n");
		printf("%d\n", run_total);
		}
		}
	}
}
