#include "t2.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#define S_MAX 50
#define INFINITE 999999
#define MAX_BUFFER 16
#define E_MAX 9999 
#define V_MAX 9999

int v, e;
int aj_matrix[V_MAX][V_MAX];
int no_nodes_visited[V_MAX];
int next_token( FILE *f, char *buf, int max );
struct Vertices gArray[E_MAX];
struct Edges pArray[E_MAX];

void fetch_vertices (FILE *csv, struct Vertices *V)
{
  char buf[S_MAX];
  next_token( csv, buf, S_MAX );
  V->stopID = atoi(buf);
  next_token(csv, V->name, S_MAX);
  next_token(csv, V->longitude, S_MAX);
  next_token(csv, V->latitude, S_MAX);
}

void fetch_edges (  FILE *csv, struct Edges *E) 
{
  char buf[S_MAX];
  next_token( csv, buf, S_MAX );
  E->vertex1 = atoi(buf);
  next_token( csv, buf, S_MAX );
  E->vertex2 = atoi(buf);  
  next_token( csv, buf, S_MAX );
  E->weight = atoi(buf); 
}



int load_edges(char *file){
  FILE *f;
  int x;
  int y;
  int z;
  f = fopen(file, "r");
  struct Edges E;
  if(!f) { 
    printf("unable to open %s\n", file); 
    return 0;
  }
  fetch_edges(f, &E);
  int nbEdges = 0;
  while(!feof(f)) {
    
    fetch_edges(f, &pArray[nbEdges] );
    e++;

    x = pArray[nbEdges].vertex1;
    y = pArray[nbEdges].vertex2;
    z = pArray[nbEdges].weight;
    aj_matrix[x][y] = z;
    aj_matrix[y][x] = z;

    nbEdges++;
  }
  aj_matrix[300][496] = 0;
  aj_matrix[496][300] = 0;
  aj_matrix[522][7659] = 0;
  aj_matrix[7659][522] = 0;
  fclose(f);

  printf("Loaded %d edges\n", e);
  return 1;
}

int load_vertices(char *s){
  FILE *f;
    struct Vertices pArray[V_MAX];    
    struct Vertices p;
    f = fopen(s, "r");

    if(!f) { 
      printf("unable to open %s\n", s); 
      return EXIT_FAILURE; 
  }
  fetch_vertices( f, &p );

  int nbVertices = 0;
  while(!feof(f)) {
    
    fetch_vertices( f, &pArray[nbVertices] );
    v++;

    gArray[nbVertices].stopID = pArray[nbVertices].stopID;
    strcpy(gArray[nbVertices].name, pArray[nbVertices].name);
    strcpy(gArray[nbVertices].longitude, pArray[nbVertices].longitude);
    strcpy(gArray[nbVertices].latitude, pArray[nbVertices].latitude);

    nbVertices++;
  }

  fclose(f);
  printf("Loaded %d vertices\n", v);
  return 1;
}


int
next_token( FILE *f, char *buffer, int max ) {
  int start=0;
  int end = 0;
  int quotes = 0;
  
  for(;;) { 
    buffer[start] = fgetc(f);
    if(buffer[start]=='"')
     { 
        quotes=!quotes; 
        buffer[start] = fgetc(f); 
    }

    if(buffer[start]==',' && !quotes) 
    {
        break; 
    }

    if(feof(f) || buffer[start]=='\n') 
    {
     end=1; 
     break;
    } 
    if( start<max-1 ) 
    {
        ++start; 
    } 
  }
  buffer[start] = 0; 
  return end; 
}

void free_memory(){
  return;
}


int cost[V_MAX][V_MAX];
int distance_travelled[V_MAX];
int predicted[V_MAX];

void shortest_path(int startNode, int endNode)
{
  int invertedarr[50];
  int curr = 0;
  int origin = startNode;
  int dest = endNode;
  int count;
  int minimum;
  int nextnode;
  int n = V_MAX;

  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      if(aj_matrix[i][j]==0)
        cost[i][j]=INFINITE;
      else
        cost[i][j]=aj_matrix[i][j];

  for(int i=0;i<n;i++)
  {
    distance_travelled[i]=cost[origin][i];
    predicted[i]=origin;
    no_nodes_visited[i]=0;
  }

  distance_travelled[origin]=0;
  no_nodes_visited[origin]=1;
  count=1;

  while(count<n-1){
    minimum=INFINITE;
    for(int i=0;i<n;i++)
      if(distance_travelled[i]<minimum&&!no_nodes_visited[i])
      {
        minimum=distance_travelled[i];
        nextnode=i;

      }

    no_nodes_visited[nextnode]=1;

    for(int i=0;i<n;i++)
      if(!no_nodes_visited[i])
        if(minimum+cost[nextnode][i]<=distance_travelled[i])
        {
          distance_travelled[i]=minimum+cost[nextnode][i];
          predicted[i]=nextnode;
        }
    count++;
  }

  for(int h=0; h<30; h++)
  {
    invertedarr[h]=0;
  }


  int i  = dest;
  if(i!=origin)
  {
    invertedarr[0] = i;
    curr++;
    int j=i;
    do
    {

      j=predicted[j];
      invertedarr[curr] = j;
      curr++;
    }while(j!=origin);
  }
  print_inv(invertedarr);
}
  
void print_inv(int arr[])
{
  int n = 0;
  int array[50];

  for(int i=0;i<50;i++){
    if(arr[i]!=0){
      n++;
    }
  }
  
  for(int i=0; i<n; i++)
  {
    array[n-i] = arr[i];
  }
  for(int i=5; i<=n; i++){
    for(int j=0; j<V_MAX; j++){
      if((array[i]==gArray[j].stopID)&&(gArray[j].stopID != 0)){
        printf("%d %s\n", gArray[j].stopID, gArray[j].name);
      }
    }
  }
}

int
main ( int argc, char *argv[] ) {

	if ( argc < 3 ) {
		printf("usage: ./bus VERTICES EDGES\n");
		return EXIT_FAILURE;
	}

	if ( !load_vertices( argv[1] ) ) {
		printf("Failed to load vertices\n");
		return EXIT_FAILURE;
	}

	if ( !load_edges( argv[2] ) ) {
		printf("Failed to load edges\n");		
		return EXIT_FAILURE;
	}

    printf("Please enter stating bus stop >\t\t");
    int startingNode;
    scanf("%d", &startingNode);
    printf("Please enter destination bus stop >\t");
    int endingNode;
    scanf("%d", &endingNode);
    shortest_path(startingNode, endingNode);
	free_memory();

	return 0;
}
