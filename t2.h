#ifndef T2_H_
#define T2_H_

#define S_MAX 50
#define INFINITE 999999
#define MAX_BUFFER 16
#define E_MAX 9999 
#define V_MAX 9999

struct Vertices {
  int stopID; 
  char name[S_MAX];
  char longitude[S_MAX];
  char latitude[S_MAX];
};

struct Edges {
  int vertex1;
  int vertex2;
  int weight;
};

int load_edges ( char *fname ); //loads the edges from the CSV file of name fname
int load_vertices ( char *fname );  //loads the vertices from the CSV file of name fname
void shortest_path(int startNode, int endNode); // prints the shortest path between startNode and endNode, if there is any
void free_memory ( void ) ; // frees any memory that was used
void print_inv(int arr[]);

#endif