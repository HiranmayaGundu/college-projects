#include "dtable.h"
#include<stdlib.h>
#include<stdio.h>

void insert(table *tab,int dat)
{
	/*
	This function inserts a value into the table at the end. If the table becomes full after 
	insert, we increase the size of the table using the given shrink factor.  
	*/
	if(tab->data == NULL)
	{	
	/* start at 16, multiplying sgrowth factor to 1 seems pointless
		and potentially dangerous as (int) 1 * 1.5 is 1, hence will be stuck
		at 1
	*/
		tab->data = (int *)malloc(sizeof(int) * 16); 
		tab->top = -1;
		tab->size = 16;	
	}
	//Increment top and input data
	tab->top++;
	tab->data[tab->top] = dat;
	// check if the table is full and do necessary adjustments
	if (tab->top == tab->size -1)
	{
		int nsize = (tab->growth * tab->size);
		printf("in insert The size is: %d\n",nsize);
		tab->data = (int *) realloc(tab->data, sizeof(int) * nsize);
		tab->size = nsize;
	} 

}

int pop(table *tab)
{
	/*
	This function removes the top element from the table. If the no of elements in 
	the table is 1 less than the size of table * shrink factor, then shrink the table.
	*/
	// basic error checking
	if(tab->top == -1)
		return -1;
	// store data, decrement top
	int dat = tab->data[tab->top];
	tab->top--;
	
	//check if table needs to be shrinked, if it does shrink it.
	int size = (tab->size * tab->shrink);
	if(tab->top == size -2 && tab->size > 16)
	{
		printf("In pop The size is: %d\n",size);
		tab->data = (int *) realloc(tab->data, sizeof(int) * size);
		tab->size = size;
	}
	return dat;
	
}
