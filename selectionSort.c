#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void selectionSort(int n, int *list)
{
	for(int i = 0; i < n-1; ++i)
	{
		int min = i;//index not value, coz we have to swap at the end**********
		for(int j = i+1; j < n; ++j)
		{
			//sleep(0.1);//1sec = 1000ms
			if(list[j] < list[min])
				min = j;
		}
		//swap(&list[i], &list[min]);
		int temp = list[i];
		list[i] = list[min];
		list[min] = temp;
	}
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
	printf("Enter the size of the list : ");
	scanf("%d", &n);
	int *list = (int*)calloc(n, sizeof(int));
	//printf("Enter the elements of the list : ");
	for(int i = 0; i < n; ++i)
		list[i] = rand() % 1000;//scanf("%d", &list[i]);
		
	printf("Before Sorting : \n");
	printList(n, list);
	
	clock_t start, end;
	start = clock();
	selectionSort(n, list);
	end = clock();
	
	printf("After Sorting : \n");
	printList(n, list);
	
	double timeReq = (double)(end-start)/CLOCKS_PER_SEC;//(double)(stop-start)************
	printf("The time it took is : %lf\n", timeReq);
	
	free(list);
	return 0;
}
