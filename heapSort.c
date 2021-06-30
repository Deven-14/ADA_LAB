#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


extern void swap(int *x, int *y);
inline void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}


void heapify(int n, int *list, int index)
{
	int parentIndex = index;
	int leftChildIndex = 2 * parentIndex + 1;
	int rightChildIndex = leftChildIndex + 1;
	
	while(leftChildIndex < n)
	{
		int greatestChildIndex = leftChildIndex;
		
		if(rightChildIndex < n && list[rightChildIndex] > list[greatestChildIndex])
			greatestChildIndex = rightChildIndex;
		
		if(list[parentIndex] > list[greatestChildIndex])
			return;
		
		swap(&list[parentIndex], &list[greatestChildIndex]);
		
		parentIndex = greatestChildIndex;
		leftChildIndex = 2 * parentIndex + 1;
		rightChildIndex = leftChildIndex + 1;
	}
}


void makeMaxHeap(int n, int *list)
{
	for(int i = n/2-1; i >=0 ; --i)
		heapify(n, list, i);
}

void heapSort(int n, int *list)
{
	makeMaxHeap(n, list);
	
	for(int i = n-1; i >= 0; --i)
	{
		swap(&list[0], &list[i]);
		heapify(i, list, 0);//list size should decrease***************8
	}
}


void printList(int n, int *list)
{
	printf("The list : ");
	
	for(int i = 0; i < n; ++i)
		printf("%d ", list[i]);
	
	printf("\n");
}


int main()
{
	int n;
	printf("Enter the size of the array : ");
	scanf("%d", &n);
	
	int *list = (int*)calloc(n, sizeof(int));// = {5, 3, 6, 2, 1};
	for(int i = 0; i < n; ++i)
		list[i] = rand()%1000;
	
	//printf("\nBefore Sorting : \n");
	//printList(n, list);
	
	clock_t start, end;
	
	start = clock();
	heapSort(n, list);
	end = clock();
	
	//printf("\nAfter Sorting : \n");
	//printList(n, list);
	
	double timeReq = (double)(end - start)/CLOCKS_PER_SEC;
	printf("The time Required is : %lf\n", timeReq);
	
	free(list);
	return 0;
}
