#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "trie.h"
#include<limits.h>

static int compare(const void *a, const void *b)
{
	/*
		Comapare function used by QSORT function. The resuls are returned in Ascending order.
	*/
	int *x = (int*)a;
	int *y = (int*)b;
	return *x-*y;
}
int isLeaf(node *son)
{
	/*
		Checks if the given node is a leaf.
	*/
	for(int i =0; i<128;i++)
	{
		if(son->child[i] != NULL)
			return 0;
	}
	return 1;
}
void nullify(node **child)
{
	/* 
		makes all the nodes null.
	*/
	for(int i =0; i<128;i++)
		child[i] = NULL;
}
void copy(node **root, node **child)
{
	/*
		Copies all the node.
	*/
	for(int i =0; i<128;i++)
		child[i] = root[i];
}

int count(node* root, int *a, int *i, int *docs, int *d)
{
	/*
		The purpose of this function is to count all the leaf nodes of the node passed to the function.
		Considered a leaf node if it has a data value greater than -1
		Store the data into array a.
		i is the index of next empty space in array.
		Docs is the array where document nos. of leaf nodes is stored. D is the index of next free space in that array.
		D is not required, but helpful in debugging (if D != no, there's a miistake)
	*/
	int n=0,l=0;
	// Default escape route. Recursive Call should never have null, but in case it does.	
	if(root == NULL)
		return 0;
	
	if(isLeaf(root) == 0)
	{
		for(int j =0; j<128; j++)
		{
			if(root->child[j] != NULL)
				n += count(root->child[j],a,i,docs,d);
		}
	}	
	else
	{
		n++;
		if(*i < 100)
		{
			
			a[*i] = root->data;
			(*i)++;
			docs[*d] = root->doc;
			(*d)++;
		}	
		if(*i >= 100)
		{
			qsort(a,100,sizeof(int),compare);
			if(a[99] > root->data)
				a[99] = root->data;
			printf("Too many hits! Will show only top 100.\n");
		}
	}
	return n;
}


int* checkPrefix(node* root,char* file,char* x, int* no, int *docs, int *d)
{

	/*
	This function finds the number of leaves to a given prefix. This is used in search.
	The parameter int* no is the number of matches, array int* gives their position. 
	Assuming a max of 100 hits.	
	
	File again gives the file as suffix tree only has indexes 
	Docs is the list of document nos found at node.
	d is the no of elements in docs, used foe debugging purposes.
	*/
	int *a = (int *) malloc(sizeof(int)*100);
	int ind;
	for(int i =0; i<100; i++)
		a[i] = INT_MAX;	
	*no = 0;
	if(root == NULL)
	{
		*no = 0;
		return NULL;
	}
	int n = strlen(x);
	int k = prefix(file,x,n,root->index.start,root->len);
	if(k == 0)
	{
		int* res;
		ind = *x;
		res = checkPrefix(root->child[ind],file,x,no,docs,d);
		qsort(a,100,sizeof(int),compare);
		qsort(docs,100,sizeof(int),compare);		
		return res;
	}	
	if(k == n)
	{
		node *temp = root;
		int c = count(temp,a,no,docs,d);	
		qsort(a,100,sizeof(int),compare);
		qsort(docs,100,sizeof(int),compare);
		return a;
	}
	if(k<n)
	{
		x = x+k;
		n -= k;
		int* res;
		ind = *x; 
		res = checkPrefix(root->child[ind],file,x,no,docs,d);
		qsort(a,100,sizeof(int),compare);	
		qsort(docs,100,sizeof(int),compare);	
		return res;
	}
}



int prefix(char* file,char* x,int n, int index, int m)
{
    /* finds the length of the biggest common prefix
        1. If common prefix = 0, go to next
        2. If common prefix is the string that is
        searched for, end.
        3. If they have a common prefix, but key is 
        not what is searched for, move using link.

		Use File for checking
		index is the start value sotred inroot.
		m is the length.
    */
    for(int k = 0; k<n; k++)
    {
        if(k ==m || x[k]!= file[k + index])
            return k;
    }
    return n;
}
void split(node* root,char* file,int k)
{
    /*
        If the text to be inserted has a common
        prefix != length of the key of the node,
        split it to insert.

		Take the current root, and a child to it where the child is
		not common prefix part. Child inherits roots children, and child 
		becomes one of the child of root.
    */

	// Create a child node
	int ind = *(file +root->index.start + k);   
	node* t = (node *) malloc(sizeof(node));
    t->len = root->len-k;
    t->data = root->data;
	t->index.start = root->index.start + k;
	t->index.end = t->index.start + t->len -1;
	t->doc = root->doc;	
	
	// make sure new split child has the child of the root. This is because
	// the nodes are associated with split node and not root.
    copy(root->child,t->child);
	nullify(root->child);	
	root->child[ind] = t;

	//Change Roots values to reflect the changes

    root->len = k;
	root->index.end = root->index.start + k -1; 
    root->data = -1;
	root->doc = -1;
}

node* pinsert(node* root,char* file,char* x,int data, int st, int doc)
{

	/*
		Use this to insert nodes into a patrica trie.
		To avoid the cost of string copy, which is O(n)
		we need a copy of the overall file which is provided by char* file.
		x is the string that is being inserted into the node.
		Data is the suffix no.
		st is the start index.
		doc is the document no from where it originates.
	*/
    int n = strlen(x) + 1;
	int ind;
    if( root == NULL)
    {
        root = (node*) malloc(sizeof(node));
        root->len = n;
        root->data = data;
        nullify(root->child);
		root->index.start = st;
		root->index.end = root->index.start + n-1;
		root->doc = doc;
        return root;
    }
    int k = prefix(file,x,n,root->index.start,root->len);
   
    if( k == 0)
	{
		ind = *x;
        root->child[ind] = pinsert(root->child[ind],file,x,data,st,doc);
	}
    else if(k < n)
    {
        if( k < root->len)
            split(root,file,k);
		ind = *(x+k);        
		root->child[ind] = pinsert (root->child[ind],file,x+k,data,st + k,doc);
       
    }
    return root; 
}



