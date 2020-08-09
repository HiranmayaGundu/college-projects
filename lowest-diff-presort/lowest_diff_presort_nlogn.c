#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
void SelectionSort(int *arr,int size);
int minDiff(int *arr, int size);
struct timespec start,end;
int main()
{
	int size, *arr;
	scanf("%d",&size);
	double ms;
	arr = (int *) malloc(sizeof(int) * size);
	for(int i =0; i<size;i++)
		scanf("%d",&arr[i]);
	
	clock_gettime(CLOCK_REALTIME, &start);
	int diff = minDiff(arr,size);
	clock_gettime(CLOCK_REALTIME, &end);
	printf("The minimum difference is: %d\n",diff);
	ms = ((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_nsec - start.tv_nsec) * 0.000001 );
	printf("ms: %f\n", ms);  
	return 0;
}
void SelectionSort(int *arr,int size)
{
	int temp, minPos;
	for(int i = 0; i< size -1; i++)
	{
		minPos = i;
		for(int j = i; j < size; j++)
		{
			if(arr[minPos] > arr[j])
				minPos = j;	
		}
	 	temp = arr[minPos];
		arr[minPos] = arr[i];
		arr[i] = temp;
	} 
}
int minDiff(int *arr, int size)
{
   SelectionSort(arr,size); 
   int diff = INT_MAX;
   for (int i=0; i<size-1; i++)
      if (arr[i+1] - arr[i] < diff)
          diff = arr[i+1] - arr[i];
   return diff;
}
