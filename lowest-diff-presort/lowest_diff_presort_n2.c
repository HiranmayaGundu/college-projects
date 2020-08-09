#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
void QuickSort(int *arr,int l, int r);
int partition(int *arr, int l, int r);
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
void QuickSort(int *arr, int l, int r)
{
	if(l < r)
	{
		
		int s = partition(arr,l , r); 
		QuickSort(arr,l,s-1);
		QuickSort(arr,s+1,r);
	}
}
int partition(int *arr, int l, int r)
{
	int pivot = arr[l];
	int i = l+1;
	int j = r;
	int temp,temp1;
	do{
		while(arr[i] <= pivot && (i < r+1))
			i++;
		while(arr[j] > pivot && (j > l))
			j--;
		 
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
		 

	}while( i < j);
	 
	temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
		temp1 = arr[l];
	arr[l] = arr[j];
	arr[j] = temp1;
	
	return j;
}
int minDiff(int *arr, int size)
{
   QuickSort(arr,0,size-1); 
   int diff = INT_MAX;
   for (int i=0; i<size-1; i++)
      if (arr[i+1] - arr[i] < diff)
          diff = arr[i+1] - arr[i];
   return diff;
}
