#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

extern void swap(int *, int *);
inline void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

int partition(int a[], int low, int high)
{
	int p = low++;
	
	while(a[high] > a[p])
		--high;
	while(low < high && a[low] <= a[p])
		++low;
	while(low < high)
	{
		swap(&a[low++], &a[high--]);
		while(a[high] > a[p])
			--high;
		while(a[low] <= a[p])
			++low;
		//sleep(0.1);
	}
	swap(&a[high], &a[p]);

	return high;		
}

void quickSort(int a[], int low, int high)
{
	if(low >= high)
		return;
	
	int p = partition(a, low, high);
	
	quickSort(a, low, p-1);
	quickSort(a, p+1, high);
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
	int n = 5;
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
	quickSort(list, 0, n-1);
	end = clock();
	
	printf("After Sorting : \n");
	printList(n, list);
	
	double timeReq = (double)(end-start)/CLOCKS_PER_SEC;//(double)(stop-start)************
	printf("The time it took is : %lf\n", timeReq);
	
	free(list);
	return 0;
}
