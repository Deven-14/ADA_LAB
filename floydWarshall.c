#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>

void printShortestPath(int V, int **D);//[V][V]);

void floydWarshall(int V, int **graph)//[V][V])
{
	//int D[V][V];
	int **D = (int**)calloc(V, sizeof(int*)); 
    for(int i = 0; i < V; ++i)
    	D[i] = (int*)calloc(V, sizeof(int));
	
	int infinity = INT_MAX;
	
	for(int i = 0; i < V; ++i)
		for(int j = 0; j < V; ++j)
			D[i][j] = graph[i][j];
	
	for(int k = 0; k < V; ++k)
	{
		for(int i = 0; i < V; ++i)
		{
			for(int j = 0; j < V; ++j)
			{
				if(D[i][k] != infinity && D[k][j] != infinity && (D[i][k] + D[k][j]) < D[i][j])
					D[i][j] = D[i][k] + D[k][j];
			}
		}
	}
	
	//printShortestPath(V, D);
	for(int i = 0; i < V; ++i)
    	free(D[i]);
    free(D);
}

void printShortestPath(int V, int **D)//[V][V])
{
	int infinity = INT_MAX;

	printf("\n");
	
	for(int i = 0; i < V; ++i)
	{
		for(int j = 0; j < V; ++j)
		{
			if(D[i][j] == infinity)
				printf("INF ");
			else
				printf("%d ", D[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int V = 4;
	printf("Enter the number of vertices : ");
	scanf("%d", &V);

	int infinity = INT_MAX;
	
	//int graph[V][V];
	/* = {
		{0 , infinity, 3, infinity},
		{2 , 0, infinity, infinity},
		{infinity, 7, 0, 1},
		{6, infinity, infinity, 0}
	};*/

    int **graph = (int**)calloc(V, sizeof(int*)); 
    for(int i = 0; i < V; ++i)
    	graph[i] = (int*)calloc(V, sizeof(int));

	for(int i = 0; i < V; ++i)
	{
		for(int j = 0; j < V; ++j)
		{
			if(i == j)
				graph[i][j] = 0;
			else if(rand()%4)
				graph[i][j] = rand()%30 + 1;
			else
				graph[i][j] = infinity;
		}
	}
	
	//printShortestPath(V, graph);
	
	clock_t start, end;
	
	start = clock();
	floydWarshall(V, graph);
	end = clock();

	//printShortestPath(V, graph);

    printf("Time Required : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

	for(int i = 0; i < V; ++i)
    	free(graph[i]);
    free(graph);

	return 0;
}
