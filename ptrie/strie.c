#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trie.h"
#include<limits.h>
#include "strie.h"

node* sinsert(node* root, char* data, int* docin)
{
	/*
		This does a suffix tree insert. Manually generate all the suffixes, and send them into the tree.
		Can be used to make a GST by giving start at 0 each time. 
		If a GST with different data values are required, vary start.
		docin is the array of integers with the index of the title for each document.
	*/
	int start = 1;
	int doc = 0;
	int nos = 0;
	docin[0] = 0;
	if(root == NULL)
	{
		//Need to create the dummy entry node;
		root = (node*) malloc(sizeof(node));
        root->len = -1;
        root->data = -1;
        nullify(root->child);
		root->index.start = -1;
		root->index.end = -1;
		root->doc = -1;
	}
	int len = strlen(data);
	char *file = (char *)malloc(sizeof(char)*len+1);
	strcpy(file,data); 
	int k = 0;
	while(*data != '\0')
	{
		
		if(*data == '\n')
		{
			
			if(*(data-1) == '\n')
			{	doc++;
				if(*(data + 1) == '\n')
					docin[doc] = start+1;
				else				
					docin[doc] = start;
			}
		}
		
		root = pinsert(root,file,data,start,k,doc);
		start++;
		len--;
		data++;
		k++;
	}
	return root;	
}
void query(node* root,char *file,char *string, int *docin)
{
	/*
		Looks for exact match, case-sensitive. root is the tree, file is the input file, 
		string is the query and docin is the starting point for title names for each document.

	*/
	int d= 0;
	int qlen = strlen(string);
	int flen = strlen(file);
	int* docs = (int *)malloc(sizeof(int)*100);
	for(int i =0; i<100; i++)
		docs[i] = INT_MAX;	
	int no = -1;   
	int* res = checkPrefix(root,file,string,&no,docs,&d);
	printf("Total number of results: %d\n\n",no);
	printf("Shift Value  Doc Value         Title\n");
	for(int i = 0; i< no; i++)
	{
		printf("%d\t\t",res[i]);
		printf("%d\t\t",docs[i] + 1);
		int j = 0;
		while(*(file+docin[docs[i]]+ j) != '\n')
		{	printf("%c",*(file+docin[docs[i]]+j));
			j++;
		}
		int s = -15;
		printf("\n");
		printf("Surrounding Text: \n");		
		while(s < qlen + 15)
		{
			if(res[i] + s < -1)
				s = 0;
			if(res[i] + s > flen)
				s = flen;
			printf("%c",*(file+res[i]+s));
			s++;
		}
		printf("\n\n");
		printf("--------------------------------");
		printf("\n\n");	
	}

}

void query2(node* root,char *file,char *string, int *docin)
{
	/*
		Looks for exact match, case-sensitive. If there is no match, look for substrings
		from the right, i.e, if wolfs is not found, look for wolf. 
		
		root is the tree, file is the input file, string is the query and docin is the 
		starting point for title names for each document.

	*/
	int d= 0;
	int qlen = strlen(string);
	int flen = strlen(file);
	int* docs = (int *)malloc(sizeof(int)*100);
	for(int i =0; i<100; i++)
		docs[i] = INT_MAX;	
	int no = -1;   
	int* res = checkPrefix(root,file,string,&no,docs,&d);
	int count = 0;
	int curDoc = -1;
	printf("\nNow searching for:%s\n",string);
	printf("Shift Value  Doc Value          Title\n");
	for(int i = 0; i< no; i++)
	{
		if(docs[i] != curDoc)
		{
			count++;
			printf("%d\t\t",res[i]);
			printf("%d\t\t",docs[i]);
			int j = 0;
			while(*(file+docin[docs[i]]+ j) != '\n')
			{	
				printf("%c",*(file+docin[docs[i]]+j));
				j++;
			}
			int s = -15;
			printf("\n");
			printf("Surrounding Text: \n");		
			while(s < qlen + 15)
			{
				if(res[i] + s < -1)
					s = 0;
				if(res[i] + s > flen)
					s = flen;
				printf("%c",*(file+res[i]+s));
				s++;
			}
			printf("\n\n");
			printf("--------------------------------");
			printf("\n\n");	
		}
		curDoc = docs[i];
	
	}
	printf("%d / %d results shown.\n",count,no);
	if(no == 0)
	{
		char *ns = (char *)malloc(sizeof(char)*qlen);
		strncpy(ns,string,qlen-1);
		ns[qlen-1] = 0;
		query2(root,file,ns,docin);
	}
	else return;
}

void relevance(node* root,char *file,char *string, int *docin)
{
	/* Highest relevance of INT_MAX is given to exact match. All documents with exact match are of same relevance.
	Then, a summantion of count for each word in the query is done. Relvance is given based on count.
	0 is given to documents of no relevance.

	Assuming the query has less than a hundred words.

	root is the tree, file is the input file, string is the query and docin is the 
	starting point for title names for each document.

    */
	rev rel[500];
	for(int i =0; i<500; i++)
	{
		rel[i].doc = i;
		rel[i].count = 0;
		rel[i].score = 0;
	}
	
	int d= 0;
	int qlen = strlen(string);
	int flen = strlen(file);
	int* docs = (int *)malloc(sizeof(int)*100);
	for(int i =0; i<100; i++)
		docs[i] = INT_MAX;	
	int no = -1;   
	int* res = checkPrefix(root,file,string,&no,docs,&d);
	
	for(int i = 0; i< no; i++)
	{
		rel[docs[i]].score = INT_MAX;
	}
	char *temp = (char *) malloc(sizeof(char)*qlen+1);
	strcpy(temp,string);
	char *word = strtok(temp," .?\";\',");
	while(word != NULL)
	{
		//printf("checking word: %s",word);
		int d= 0;
		int qlen = strlen(string);
		int flen = strlen(file);
		int* docs = (int *)malloc(sizeof(int)*100);
		for(int i =0; i<100; i++)
			docs[i] = INT_MAX;	
		int no = -1;   
		int* res = checkPrefix(root,file,word,&no,docs,&d);
		for(int i = 0; i< no; i++)
		{
			rel[docs[i]].count += 1;
		}
		word = strtok(NULL," .?\";\',");
	}
	qsort(rel,500,sizeof(rev),compare1);
	int curCount = rel[0].count;
	int scr = INT_MAX - 1;	
	for(int i =0; i<no; i++)
	{
		if(rel[i].score == INT_MAX)
			continue;
		if(rel[i].count != curCount)
			scr--;
		rel[i].score = scr;
	}
	qsort(rel,500,sizeof(rev),compare2);
	printf("Printing top 10 documents:\n\n");
	for(int i =0; i<10; i++)
	{
		int j = 0;
		while(*(file+docin[rel[i].doc]+ j) != '\n')
		{	
			printf("%c",*(file+docin[rel[i].doc]+j));
			j++;
		}
		printf("\n\n---------------------------------------\n\n");
	}
  
}

static int compare1(const void *a, const void *b)
{
	/*
		Comapare function used by QSORT function. The resuls are returned in Ascending order.
	*/
	rev *x = (rev*)a;
	rev *y = (rev*)b;
	return y->count - x->count;
}
static int compare2(const void *a, const void *b)
{
	/*
		Comapare function used by QSORT function. The resuls are returned in Ascending order.
	*/
	rev *x = (rev*)a;
	rev *y = (rev*)b;
	return y->score - x->score;
}



