#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


void merge(int *list, int low, int mid, int high)
{
	int *tempList = (int*)calloc(high - low + 1, sizeof(int));
	
	int i = low;
	int j = mid + 1;
	int k = 0;
	
	while(i <= mid && j <= high)
	{
		/*if(list[i] <= list[j])
			tempList[k++] = list[i++];
		else
			tempList[k++] = list[j++];*///3 compares here, 1) i<=mid, 2)j<=high, 3)list[i]<=list[j]
		
		//only 2 compares in this method
		while(i <= mid && list[i] <= list[j])
			tempList[k++] = list[i++];
		
		while(j <= high && list[j] <= list[i])
			tempList[k++] = list[j++];
		//sleep(0.0001);
	}
	
	if(i > mid)
		while(j <= high)
			tempList[k++] = list[j++];
	else
		while(i <= mid)
			tempList[k++] = list[i++];
	
	
	for(int l = low, k = 0; l <= high; ++l, ++k)
		list[l] = tempList[k];
	
	free(tempList);
}

void mergeSortUtil(int *list, int low, int high)
{
	if(low >= high)
		return;
	int mid = low + (high - low) / 2;
	mergeSortUtil(list, low, mid);
	mergeSortUtil(list, mid + 1, high);
	merge(list, low, mid, high);
}

void mergeSort(int *list, int n)
{
	if(n <= 0)
		return;
	mergeSortUtil(list, 0, n - 1);
}

void printList(int n, int *list)
{
	if(n <= 0)
	{
		printf("The list is empty\n");
		return;
	}
	
	printf("The list is : ");
	for(int i = 0; i < n; ++i)
		printf("%d ", list[i]);
	printf("\n");
}

int main()
{
	int n;
	printf("Enter the size of the array : ");
	scanf("%d", &n);
	
	int *list = (int*)calloc(n, sizeof(int));
	for(int i = 0; i < n; ++i)
		list[i] = rand() % 1000;
	
	printf("Before Sorting : ");
	printList(n, list);
	
	clock_t start, end;
	
	start = clock();
	mergeSort(list, n);
	end = clock();
	
	printf("\nAfter Sorting : ");
	printList(n, list);
	
	double timeReq = (double)(end - start) / CLOCKS_PER_SEC;
	printf("\nThe time required for the merge sort algorithm is : %lf \n", timeReq);
	
	free(list);
	return 0;
}
