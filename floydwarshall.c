#include<stdio.h>
#include <stdlib.h>
#include <time.h>

 clock_t base, total;

// Number of vertices in the graph
#define V 1000
#define START_TIMER  base = clock();
#define PAUSE_TIMER  total += (clock() - base);

 
/* Define Infinite as a large enough value. This value will be used
  for vertices not connected to each other */
#define INF 99999
 

void printSolution(int **dist);
// Solves the all-pairs shortest path problem using Floyd Warshall algorithm
void floydWarshall (int **graph)
{
    /* dist[][] will be the output matrix that will have the shortest 
      distances between every pair of vertices */
    int **dist, i, j, k;
    dist=(int **)malloc(V*sizeof(int *));
    for(i=0;i<V;i++)
	  dist[i]=(int *)malloc(V*sizeof(int *));
    /* Initialize the solution matrix same as input graph matrix.*/
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
 
    int temp1;
    for (k = 0; k < V; k++)
    {
        // Pick all vertices as source one by one
       // #pragma omp parallel for num_threads(2)   Uncomment this line to parallelise using OpenMP 
        for (i = 0; i < V; i++)
        {
            // Pick all vertices as destination for the
            // above picked source
	          //temp1=dist[i][k];	
	        //if(dist[i][k]!=INF)     Uncomment this line to optimise the code.You'll see the performance gain in time taken
            for (j = 0; j < V; j++)
            {
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
               
		        if(dist[k][j] != INF) {
          	  	int temp = dist[k][j]+dist[i][k];
        	  	  if(dist[i][j] == INF || temp < dist[i][j]) {
            			  dist[i][j] = temp;
			          }
        	    }
            }
        }
    }
 
    // Print the shortest distance matrix
    printSolution(dist);
}
 
/* A utility function to print solution */
void printSolution(int **dist)
{
    printf ("Following matrix shows the all-pair shortest distances between every pair of vertices \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
for(i=0;i<V;i++)
free(dist[i]);
free(dist);
}
 
// driver program to test above function
int main(int argc,char *argv)
{
int c,i,c2, n=100;
int r;
int **graph;
graph=(int **)malloc(V*sizeof(int *));
for(i=0;i<V;i++)
	graph[i]=(int *)malloc(V*sizeof(int *));

//Generate a Matrix that represents a typical graph.
//Using rand function to generate random numbers for the graph.

for (c2 = 0; c2 < V; c2++){
   for (c = 0; c < V; c++){
	    if(c==c2) graph[c2][c]=0;
	    else if(c2>c) graph[c2][c]=INF;
	    else {
    		r = rand() % 20 + 1;
		    if(r==19||r==9) graph[c2][c]=INF;
		    else  graph[c2][c]=r;
   		}
		//printf("%d ",graph[c2][c]);
  }
//printf("\n");
}  
printf("start:\n");
// Print the solution
START_TIMER
    floydWarshall(graph);
PAUSE_TIMER
printf("Time: %ld\n", total/1000);
for(i=0;i<V;i++)
    free(graph[i]);
free(graph);
return 0;
}
