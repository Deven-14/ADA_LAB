#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct edge
{
	int src;
	int dest;
	int weight;
};
typedef struct edge Edge;

struct graph
{
	int nVertices;
	int nEdges;
	Edge *edges;
};
typedef struct graph Graph;

Graph* newGraph(int nVertices, int nEdges)
{
	Graph *g = (Graph*)malloc(sizeof(Graph));
	
	g->nVertices = nVertices;
	g->nEdges = nEdges;
	
	g->edges = (Edge*)calloc(nEdges, sizeof(Edge));
	
	return g;
}

Graph* input()
{
	int v, e;
	printf("Enter the number of vertices : ");
	scanf("%d", &v);
	printf("Enter the number of edges : ");
	scanf("%d", &e);

	Graph *g = newGraph(v, e);
	
	//printf("Enter the edges (i.e src vertex, dest vertex, it's weight)\n");
	for(int i = 0; i < e; ++i)
	{
		g->edges[i].src = rand()%v;
		g->edges[i].dest = rand()%v;
		g->edges[i].weight = rand()%10;
		
	}
		//scanf("%d %d %d", &g->edges[i].src, &g->edges[i].dest, &g->edges[i].weight);
	
	return g;
}	 
/*struct vertice
{
	int value;// here don't need values as the array index will be the vertice value.
	int parent;
};*///pass vertices[] instead of n and parent in find and union, compare by compare func.

//or map i.e map<int, int> vertices; vertices[value] = parent;//better this way

int find(int n, int *parent, int index)
{
    if(index >= n)
        return -1;
    
    int parentIndex = -1;
    int i = index;
    
    while(parent[i] >= 0)
        i = parent[i];
    
    parentIndex = i;

    while(index != parentIndex)
    {
        int nextIndex = parent[index];
        parent[index] = parentIndex;
        index = nextIndex;
    }
    
    return parentIndex;
}

void Union(int n, int *parent, int indexOne, int indexTwo)
{
    int parentIndexOne = indexOne;//find(n, parent, indexOne);
    int parentIndexTwo = indexTwo;//find(n, parent, indexTwo);
    
    //if(parentIndexOne == parentIndexTwo)
    //    return;
    
    int total = parent[parentIndexOne] + parent[parentIndexTwo];
    
    if(parent[parentIndexOne] < parent[parentIndexTwo])
    {
        parent[parentIndexTwo] = parentIndexOne;
        parent[parentIndexOne] = total;
    }
    else
    {
        parent[parentIndexOne] = parentIndexTwo;
        parent[parentIndexTwo] = total;
    }
}

int compare(const void *a, const void *b)
{
	Edge *e1 = (Edge*)a, *e2 = (Edge*)b;
	return e1->weight > e2->weight;
}

Graph* kruskalMST(Graph *forest)
{
	Graph *mst = newGraph(forest->nVertices, forest->nVertices - 1);
	
	int nV = forest->nVertices;
	int *vertices = (int*)calloc(forest->nVertices, sizeof(int));
	
	for(int i = 0; i < nV; ++i)
		vertices[i] = -1;

	qsort(forest->edges, forest->nEdges, sizeof(forest->edges[0]), compare);
	
	int i = 0, ecounter = 0;
	
	while(i < forest->nEdges && ecounter < forest->nVertices-1)
	{
		Edge temp = forest->edges[i++];
		int indexOne = find(nV, vertices, temp.src);
		int indexTwo = find(nV, vertices, temp.dest);
		
		if(indexOne == indexTwo)
			continue;
		
		Union(nV, vertices, indexOne, indexTwo);
		mst->edges[ecounter++] = temp;
	}
	
	mst->nEdges = ecounter;//*********************coz initially we say no of edges = vertices-1, but that might not be the case at random input so this, more space is allocated to edges but we don't need nedges to free space
	
	free(vertices);
	return mst;
}

int calculateWeight(Graph *g)
{
	int sum = 0;
	for(int i = 0; i < g->nEdges; ++i)
		sum += g->edges[i].weight;
	return sum;
}

void printGraph(Graph *g)
{
	printf("The mst graph is : \n");
	for(int i = 0; i < g->nEdges; ++i)
		printf("%d -- %d == %d\n", g->edges[i].src, g->edges[i].dest, g->edges[i].weight);
	printf("The weight of the mst graph is : %d\n", calculateWeight(g));
}

void freeGraph(Graph **g)
{
	free((*g)->edges);
	free(*g);
	*g = NULL;
}

int main()
{
	Graph *forest = input();
	
	clock_t start, end;
	start = clock();
	Graph *mst = kruskalMST(forest);
	end = clock();
	
	double timeReq = ((double)end - start)/CLOCKS_PER_SEC;
	
	printf("The time it took is : %lf\n", timeReq);
	
	//printGraph(mst);
	freeGraph(&forest);
	freeGraph(&mst);
	return 0;
}
