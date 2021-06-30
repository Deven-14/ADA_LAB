#include <bits/stdc++.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
using namespace std;

// number of total nodes
//const int N = 5;
const int INF = INT_MAX;

class Node
{
	public:
		const int N;
		vector<pair<int, int>> path;
		int **matrix_reduced;
		int cost;
		int vertex;
		int level;
		
		Node(int n): N(n)
		{
			matrix_reduced = new int*[N];
			for(int i = 0; i < N; ++i)
				matrix_reduced[i] = new int[N];
		}
		
		~Node()
		{
			for(int i = 0; i < N; ++i)
				delete[] matrix_reduced[i];
			delete[] matrix_reduced;
		}
};

Node* newNode(int N, int **matrix_parent, vector<pair<int, int>> const &path,int level, int i, int j)
{
    Node* node = new Node(N);
    
    node->path = path;
    
    if (level != 0)
        node->path.push_back(make_pair(i, j));
        
    //memcpy(node->matrix_reduced, matrix_parent, sizeof node->matrix_reduced);
    for(int i = 0; i < N; ++i)
    	for(int j = 0; j < N; ++j)
    		node->matrix_reduced[i][j] = matrix_parent[i][j];
    
    for (int k = 0; level != 0 && k < N; k++)
    {
        node->matrix_reduced[i][k] = INF;
        node->matrix_reduced[k][j] = INF;
    }

    node->matrix_reduced[j][0] = INF;
    node->level = level;
    node->vertex = j;
    
    return node;
}

void reduce_row(int N, int **matrix_reduced, int row[])
{
    fill_n(row, N, INF);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix_reduced[i][j] < row[i])
                row[i] = matrix_reduced[i][j];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix_reduced[i][j] != INF && row[i] != INF)
                matrix_reduced[i][j] -= row[i];
}

void reduce_column(int N, int **matrix_reduced, int col[])
{
    fill_n(col, N, INF);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix_reduced[i][j] < col[j])
                col[j] = matrix_reduced[i][j];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (matrix_reduced[i][j] != INF && col[j] != INF)
                matrix_reduced[i][j] -= col[j];
}

int cost_calculation(int N, int **matrix_reduced)
{
    int cost = 0;

    int row[N];
    reduce_row(N, matrix_reduced, row);

    int col[N];
    reduce_column(N, matrix_reduced, col);

    for (int i = 0; i < N; i++)
        cost += (row[i] != INT_MAX) ? row[i] : 0,
            cost += (col[i] != INT_MAX) ? col[i] : 0;

    return cost;
}

void printPath(vector<pair<int, int>> const &list)
{
	cout << "Path : " << endl;
	
    for (int i = 0; i < list.size(); i++)
        cout << list[i].first + 1 << " -> "
             << list[i].second + 1 << endl;
}

class comp {
public:
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return lhs->cost > rhs->cost;
    }
};

int solve(int N, int **adjacensyMatrix)
{
    priority_queue<Node*, std::vector<Node*>, comp> pq;
    vector<pair<int, int>> v;
    Node* root = newNode(N, adjacensyMatrix, v, 0, -1, 0);
    root->cost = cost_calculation(N, root->matrix_reduced);
    pq.push(root);
    while (!pq.empty())
    {
        Node* min = pq.top();
        pq.pop();
        int i = min->vertex;
        if (min->level == N - 1)
        {
            min->path.push_back(make_pair(i, 0));
            printPath(min->path);
            
            int minCost = min->cost;
            delete min;
            
            while(!pq.empty())
			{
				Node* temp = pq.top();
				pq.pop();
				delete temp;
			}
			
            return minCost;
        }

        for (int j = 0; j < N; j++)
        {
            if (min->matrix_reduced[i][j] != INF)
            {
                Node* child = newNode(N, min->matrix_reduced, min->path,
                    min->level + 1, i, j);

                child->cost = min->cost + min->matrix_reduced[i][j]
                            + cost_calculation(N, child->matrix_reduced);

                pq.push(child);
            }
        }

        delete min;
    }
    
    return -1;
}

int main()
{

	int N;
	
	cout << "Enter the number of vertices : ";
	cin >> N;

    int **adjacensyMatrix = new int*[N]; //[N][N];
    for(int i = 0; i < N; ++i)
    	adjacensyMatrix[i] = new int[N];
    // =
    /*{
        { INF, 20, 30, 10, 11 },
        { 15,  INF, 16,  4,  2 },
        { 3,   5,  INF, 2,  4 },
        { 19,   6,   18,   INF, 3 },
        { 16,   4,   7,   16, INF }
    };*/
	
	srand(time(0));

	for(int i = 0; i < N; ++i)
	{
		for(int j = 0; j < N; ++j)
		{
			if(i == j)
				adjacensyMatrix[i][j] = INF;
			else
				adjacensyMatrix[i][j] = rand()%30 + 1;
		}
	}
	
	clock_t start, end;
	
	start = clock();
	int totalCost = solve(N, adjacensyMatrix);
	end = clock();
	
    cout << "\nCost : " << totalCost << endl;
    cout << "Time Required : " << static_cast<double>(end - start) / CLOCKS_PER_SEC << endl;


	for(int i = 0; i < N; ++i)
    	delete[] adjacensyMatrix[i];
    delete[] adjacensyMatrix;

    return 0;
}
