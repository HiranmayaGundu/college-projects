#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#ifndef _TRIEH_
#define _TRIEH_

typedef struct inde{
	int start;
	int end;
}inde;

typedef struct node
{
//   char* key;
	int data;	
	int len;	
	struct inde index;	
	int doc;	
    struct node* child[128];
 
}node;


int prefix(char*,char*, int,int,int);
node* find(node*,char*,int);
void split(node*,char*,int);
node* pinsert(node* ,char*,char*, int,int,int);
void join(node*);
node* del(node*, char*, int);
int* checkPrefix(node*,char*, char*,int*,int *, int * );
int count(node*, int *, int *,int *, int *);
static int compare(const void *, const void *);
void nullify(node**);
void copy(node**, node**);

#endif
