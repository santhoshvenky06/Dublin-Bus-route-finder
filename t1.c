#include <stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include "t1.h"
#define MAX 50

struct Graph* create_graph(int num_nodes); 
void add_edge(struct Graph *g, int from, int to); 
void bfs(struct Graph* g, int origin); 
void dfs(struct Graph* g, int origin); 
void print_graph(struct Graph* g);

/*static int char2val ( char c ) {
	if ( c < 'A' || c > 'Z' ) {
		return -1;
	}
	return c-'A';
}*/

int int2char(int data){

	if(data < 0 || data>25)
        printf("not in dataset\n");
    else 
        return data + 'A';
}

Graph* create_graph(int num_nodes) 
{
	Graph* g = malloc(sizeof(Graph));
    g->no_nodes = num_nodes;
    g->array = malloc(num_nodes * sizeof(struct ajlist*));
	g->no_nodes_visited = malloc(num_nodes * sizeof(int));
    for (int i = 0; i < num_nodes; i++)
	{
    	g->array[i] = NULL;
        g->no_nodes_visited[i] = 0;
	}
    return g;
}

void print_graph(Graph* g) 
{	
	printf("\n");
	int i;
    for (i = 0; i < g->no_nodes; i++)
    {
        ajlist* p = g->array[i];
		printf("%c ", int2char(i));
        while (p)
        {
			printf(" -> %c ", int2char(p->destination));
        	p = p->next;
  
        }
		printf("\n");
    }

}

struct Queue* create_q() {
	 Queue* q = malloc(sizeof(Queue));
	q->front = q->rear = -1;
	return q;
}
	
bool isQempty(Queue* q) {
	if (q->rear == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}	

void enqueue(Queue* q, int data) {
	if (q->rear == MAX - 1)
	{
		printf("\nOh no!, The Queue is full");
	}

	else 
    {
    	if (q->front == -1)
    	{
    		q->front = 0;
		}
    	q->rear++;
    	q->value[q->rear] = data;
	}
}

int dequeue(Queue* q) {
	int temp;
	if (isQempty(q)) 
	{
    	printf("Oh no! The Queue is empty");
    	temp = -1;
	} 
	else 
	{
		temp = q->value[q->front];
		q->front++;
    	if (q->front > q->rear) 
		{

      		q->front = q->rear = -1;
    	}
	}
	return temp;
}


void printQueue(Queue* q) {

	if (isQempty(q)) 
	{
    	printf("Oh no! The Queue is empty");
	} 
	else 
	{
    	for (int i = q->front; i < q->rear + 1; i++) 
		{
      		printf("%c ", int2char(q->value[i]));
    	}
    }
}


ajlist* list(int temp)
{
    ajlist* node = malloc(sizeof(ajlist));
    node->destination = temp;
    node->next = NULL;
    return node;
};

void add_edge(Graph *g, int from, int to) 
{
	ajlist* node = list(to);
    node->next = g->array[from];
    g->array[from] = node;
}

int counter(Graph* g, int origin){
	
	Queue* q = create_q();
	
	g->no_nodes_visited[origin] = 1;
	int x = 0;
	x++;
	
	while (!isQempty(q)) 
	{
		
		int currentVertex = dequeue(q);		
		ajlist* buffer = g->array[currentVertex];
		
		while (buffer) 
		{
			int vertex = buffer->destination;
			
			if (g->no_nodes_visited[vertex] == 0) 
			{
				g->no_nodes_visited[vertex] = 1;
				x++;
			}
			buffer = buffer->next;
		}
	}
	free(q);
	return x;
}

void bfs(Graph* g, int origin)
{
	Queue* q = create_q();
	printf("\n");
	printf("BFS:");
	g->no_nodes_visited[origin] = 1;
	enqueue(q, origin);
	
	while (!isQempty(q)) 
	{
		
		int curr = dequeue(q);	
		printf(" %c ", int2char(curr));
		ajlist* buffer = g->array[curr];
		
		while (buffer) 
		{
			int vertex = buffer->destination;
			
			if (g->no_nodes_visited[vertex] == 0) 
			{
				g->no_nodes_visited[vertex] = 1;
				enqueue(q, vertex);
			}
			buffer = buffer->next;
		}
	}
	for(int j=0; j<g->no_nodes; j++){
		g->no_nodes_visited[j]=0;
	}
	free(q);
}

void dfs(Graph* g, int origin) 
{	
	static int current= 0;
	
	ajlist* arrays  = g->array[origin];
	ajlist* buffer = arrays;
    static int temp = 0;
	if(temp == 0){
		printf("DFS:");
		temp++;
	}
	
	g->no_nodes_visited[origin] = 1;

	printf(" %c ", int2char(origin));

	while (buffer != NULL) {
    int final_node = buffer->destination;

    if (g->no_nodes_visited[final_node] == 0) 
	{
		dfs(g, final_node);
		current++;
    }
	buffer = buffer->next;
	}
	if((current+1) == g->no_nodes){
		for(int j=0; j<g->no_nodes; j++){
			g->no_nodes_visited[j]=0;
		}	
	}
}


void delete_graph(Graph* g) 
{
    for (int i = 0; i < g->no_nodes; i++)
    {
        ajlist* temp = g->array[i];

        while (temp!=0)
        {	
        	ajlist* x;
        	x = temp;
        	temp = temp->next;
            free(x);
        }

    }
    free(g->array);
    free(g->no_nodes_visited);
    free(g);

}

/*int main() {
    int num_nodes = 7;
    Graph *graph = create_graph(num_nodes);
   
    add_edge(graph, char2val('A'), char2val('E'));
    add_edge(graph, char2val('B'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('B'));
    add_edge(graph, char2val('B'), char2val('C'));  
    add_edge(graph, char2val('C'), char2val('B'));
    add_edge(graph, char2val('E'), char2val('D'));
    add_edge(graph, char2val('D'), char2val('F'));
    add_edge(graph, char2val('F'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('D'));
    add_edge(graph, char2val('D'), char2val('G'));
    dfs(graph, char2val('A'));
    bfs(graph, char2val('A'));
    delete_graph(graph);

}*/
