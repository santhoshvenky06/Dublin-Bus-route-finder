#ifndef T1_H_
#define T1_H_
#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef struct ajlist ajlist;
struct ajlist
{   int destination;
    struct ajlist* next;
};
  
typedef struct Queue Queue;
struct Queue {
	int value[MAX];
	int front;
	int rear;
};

typedef struct Graph Graph;
struct Graph{

    int no_nodes; int* no_nodes_visited;
    struct ajlist** array;
};



Graph* create_graph(int num_nodes); // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
void add_edge(Graph *g, int from, int to); // adds a directed edge
void bfs(Graph* g, int origin); //implements breath first search and prints the results
void dfs(Graph* g, int origin); //implements depth first search and prints the results
void print_graph(Graph* g); // prints the graph
void delete_graph(Graph* g);

#endif