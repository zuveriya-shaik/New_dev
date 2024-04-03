#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#define MAX_VERTICES 100

int minDistance(int dist[], bool sptSet[], int V) 
{
	int min = INT_MAX, min_index;
	for (int v = 0; v < V; v++) 
	{
		if (!sptSet[v] && dist[v] <= min) 
		{
			min = dist[v];
			min_index = v;
		}
	}
	return min_index;
}

void printPath(int parent[], int j) 
{
	if (parent[j] == -1) 
	{
		printf("%c ", 'a' + j);
		return;
	}
	printPath(parent, parent[j]);
	printf("%c ", 'a' + j);
}

void printSolution(int dist[], int parent[], int src, int dest) 
{
	printf("Shortest path:\n");
	printf("From %c to %c is: ", 'a' + src, 'a' + dest);
	printPath(parent, dest);
	printf("length=%d\n", dist[dest]);
}

void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int src, int dest, int V) 
{
	int dist[MAX_VERTICES];
	bool sptSet[MAX_VERTICES];
	int parent[MAX_VERTICES];
	for (int i = 0; i < V; i++) 
	{
		dist[i] = INT_MAX;
		sptSet[i] = false;
		parent[i] = -1;
	}
	dist[src] = 0;
	for (int count = 0; count < V - 1; count++) 
	{
		int u = minDistance(dist, sptSet, V);
		sptSet[u] = true;
		for (int v = 0; v < V; v++) 
		{
			if (!sptSet[v] && graph[u][v] != -1 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) 
			{
				dist[v] = dist[u] + graph[u][v];
				parent[v] = u;
			}
		}
	}
	printSolution(dist, parent, src, dest);
}

int main() 
{
	int V;
	printf("Enter the number of nodes: ");
	scanf("%d", &V);
	int graph[MAX_VERTICES][MAX_VERTICES];
	printf("Enter the adjacency matrix for the graph (-1 for no edge):\n");
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			scanf("%d", &graph[i][j]);
	int src, dest;
	char sourceNode, destNode;
	printf("Enter the source node: ");
	scanf(" %c", &sourceNode);
	src = sourceNode - 'a';
	printf("Enter the destination node: ");
	scanf(" %c", &destNode);
	dest = destNode - 'a';
	dijkstra(graph, src, dest, V);
	return 0;
}
