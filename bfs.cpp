#include <iostream>
#include <ctime>
#include <list>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Node
{
	private:
		int data;
		list<Node*> adjacent;
		unordered_set<Node*> edges;
		
	public:
		//Node() { }
		Node(int data) : data(data) 
		{
			edges.insert(this);//for no self loop
		}
		friend class Graph;
};

class Graph
{
	private:
		unordered_map<int, Node*> nodeLookup;
		
		Node* getNode(int data)
		{ 
			if(nodeLookup.find(data) == nodeLookup.end())
				nodeLookup[data] = new Node(data);
			return nodeLookup[data];
		}
		
	public:
		
		~Graph()
		{
			for(auto &x : nodeLookup)
				delete x.second;
		}
		
		void addEdge(int source, int destination)
		{
			Node *s = getNode(source);
			Node *d = getNode(destination);
			//if(find(s->adjacent.begin(), s->adjacent.end(), d) == s->adjacent.end())//added this coz of repeated edges, i.e 1,2 and again 1,2
			if(s->edges.find(d) == s->edges.end())
			{
				s->adjacent.push_back(d);
				s->edges.insert(d);
			}
		}
		
		void BFS(int source);
};

void Graph::BFS(int source)
{
	if(nodeLookup.find(source) == nodeLookup.end())
		return;
	Node *src = getNode(source);
	queue<Node*> nextToVisit;
	unordered_set<int> visited;
	
	cout << "BFS : ";
	
	nextToVisit.push(src);
	
	while(!nextToVisit.empty())
	{
		Node *node = nextToVisit.front();
		nextToVisit.pop();
		
		if(visited.find(node->data) != visited.end())//if key is not present in visited then conti, i.e. if key is not visited then conti
			continue;
			
		cout << node->data << ", ";
		visited.insert(node->data);
		
		for(Node *n : node->adjacent)
			nextToVisit.push(n);
	}
	cout << endl;
}

int main()
{
	Graph g;
	/*g.addEdge(1, 2);
	g.addEdge(2, 5);
	g.addEdge(2, 3);
	g.addEdge(2, 4);
	g.addEdge(3, 7);
	g.addEdge(3, 6);
	
	g.addEdge(1, 2);
	auto &a = g.nodeLookup[1];
	for(auto &b : a->adjacent)
		cout << b->data << endl;*/
	g.addEdge(1, 2);
	int n;
	cout << "Enter the number of edges : ";
	cin >> n;
	srand(time(0));
	
	for(int i = 0; i < n; ++i)
		g.addEdge(rand() % 10000, rand() % 10000);
		
	clock_t start, end;	
	
	start = clock();
	g.BFS(1);
	end = clock();
	
	double timeReq = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	printf("Time Required = %lf\n", timeReq);
	//cout << "Time Required = " << timeReq << endl;
	
	return 0;
}
