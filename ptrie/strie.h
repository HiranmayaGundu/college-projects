#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<limits.h>
#include "trie.h"
#ifndef _STRIEH_
#define _STRIEH_


typedef struct rev{
	int doc;
	int score;
	int count;
}rev;

void query(node* root,char *file,char *string, int *docin);
void query2(node* root,char *file,char *string, int *docin);
void relevance(node* root,char *file,char *string, int *docin);
static int compare1(const void *a, const void *b);
static int compare2(const void *a, const void *b);
node* sinsert(node*,char*,int*);

#endif
