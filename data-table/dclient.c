#include "dtable.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<time.h>
struct timespec start,end;
int main()
{
	/* To collect the data, I am writing the timing resulsts into different files for
		insert and pop. */
	
	FILE *inserts = fopen("insert.txt","w+");
	FILE *pops = fopen("pop.txt","w+");
	double ms;
	table tab1;
	tab1.data == NULL; tab1.size = 0; tab1.top = -1; tab1.shrink = 0.25; tab1.growth = 1.25; 
	// Use tab.shrink or tab.growth to set the factors you want to use.
	srandom(getpid());	
	for(int i =0; i<1000; i++)
	{
		int val = random();
		int x = val %6;
		/*
		To generate a 4:2 ratio of inserts vs deletes, I randomly generated value and mod by 6.
		If the no is >=0 and < 4, I'm inserting into the data table. Else, I will pop.
		Similarly, I use mod 5 for making a 3:2 ratio and mod 2 for 50-50.
		
		*/
		if(x >= 0 && x < 4)
		{
			clock_gettime(CLOCK_REALTIME, &start);
			insert(&tab1,val);
			clock_gettime(CLOCK_REALTIME, &end);
			ms = ((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_nsec - start.tv_nsec) * 0.000001);
			fprintf(inserts,"%g\n",ms);
		}
		else
		{ 
			int popped;	
			clock_gettime(CLOCK_REALTIME, &start);	
			popped = pop(&tab1);
			clock_gettime(CLOCK_REALTIME, &end);
			ms = ((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_nsec - start.tv_nsec) * 0.000001);
			fprintf(pops,"%g\n",ms);
		}
	}
	fclose(inserts);
	fclose(pops);
}
