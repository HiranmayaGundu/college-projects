#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "trie.h"
#include "strie.h"
int main(int argc, char* argv[])
{
    node* root = NULL;
//	Reading the entire file using File pointers and seek
	char *file_contents;
	long input_file_size;
	FILE *input_file = fopen("data.txt", "rb");
	fseek(input_file, 0, SEEK_END);
	input_file_size = ftell(input_file);
	rewind(input_file);
	file_contents = malloc((input_file_size + 1) * (sizeof(char)));
	fread(file_contents, sizeof(char), input_file_size, input_file);
	fclose(input_file);	
	file_contents[input_file_size] = 0;
// End of file road
	int* docin = (int *) malloc(sizeof(int)*500);
	for(int i =0; i< 500; i++)
		docin[i] = -1;

	root = sinsert(root,file_contents,docin);
	int ch;
	do{
		printf("\n");
		printf("Menu:\n");
		printf("1.Query For Exact Match.\n");
		printf("2.Query For Highest Substring Match.\n");
		printf("3.Query For Relevance Score.\n");
		printf("4.Exit.\n");
		printf("Enter your choice: ");
		scanf("%d",&ch);
		char string[101];
		char *output;
		if(ch < 4)
		{	printf("Enter your query(Max 100 char): ");
			fgets(string,101,stdin); // The first gets is getting newline from previous enter, instead of flushing buffer,read twice.
			fgets(string,101,stdin);
			int len = strlen(string);
			output = (char *)malloc(sizeof(char)*len);
			strncpy(output,string,len-1);
			output[len-1] = 0;
		}		
		switch(ch)
		{
			case 1: query(root,file_contents,output,docin);break;
			case 2: query2(root,file_contents,output,docin);break;
			case 3: relevance(root,file_contents,output,docin);break;
			case 4: break;
			default: printf("Invalid input.\n");
		}
	}while(ch != 4);
	
}


