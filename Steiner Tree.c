/* 
 * Steiner Tree in Graph.
 * We need to form an MST "T" that contains all the given terminals (vertices).
 * The MST can include remaining vertices also.
 * Dijkstra's Shortest Path Algorithm is used here.
 * Initially T is empty.
 */

#include <stdio.h> 
#include <limits.h> 
#include <stdbool.h>

#define V 7     /* Number of Vertices in Graph */
#define K 3     /* Number of Terminal Vertices in MST T */

int dist[V];
int parent[V];

int T[V] = {0};      /* Set of Vertices in MST T */
int y = 0;           /* Number of Vertices in MST T */

int a[V] = {0};      /* Stores Set of Vertices in the desired Path
                        from source to destination vertex excluding the latter*/

int d = 0;           /* Number of Vertices in the desired Path 
                        from source to destination vertex excluding the latter*/


/*
 * A utility function to find the vertex with minimum distance value, from 
 * the set of vertices not yet included in shortest path tree 
 */
int minDistance(int dist[], bool sptSet[]) 
{ 
    /*
     * Initialize min value 
     */
    int min = INT_MAX, min_index; 

    for (int v = 0; v < V; v++) 
	if (sptSet[v] == false && dist[v] <= min) 
	    min = dist[v], min_index = v; 

    return min_index; 
}

void find_parent(int parent[], int j) 
{     
    /*
     * Base Case : If j is source 
     */
    if (parent[j] == - 1)  
		return; 
    
    find_parent(parent, parent[j]); 
    a[d] = j;
    d++;  
} 

/*
 * Function to print shortest path from source to j 
 * using parent array 
 */
void printPath(int parent[], int j) 
{     
    if (parent[j] == - 1)  {
		return; 
    }
    printPath(parent, parent[j]); 
    printf("%d ", j); 
} 

/*
 * A utility function to print the constructed distance array 
 */
int printSolution(int dist[], int n,int x) 
{ 
    int src = x;
    printf("Vertex \tDistance from Source\t Path"); 
	for (int i = 1; i < V; i++) 
	{
		printf("\n%d -> %d \t\t %d\t\t%d ", 
				src, i, dist[i], src); 
		printPath(parent, i); 
    }
    printf("\n");
} 

/*
 * Function that implements Dijkstra's single source shortest path algorithm 
 * for a graph represented using adjacency matrix representation 
 */
void dijkstra(int graph[V][V], int src) 
{ 
    // The output array. dist[i] will hold the shortest 
    // distance from src to i 
    
    //int dist[V];

    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in 
    // shortest  path tree or shortest distance from src to i is finalized 

    // Initialize all distances as INFINITE and stpSet[] as false 
    for (int i = 0; i < V; i++) 
		dist[i] = INT_MAX, sptSet[i] = false, parent[i] = -1; 

    // Distance of source vertex from itself is always 0 
    dist[src] = 0; 

    // Find shortest path for all vertices 
    for (int count = 0; count < V; count++) 
    { 
		// Pick the minimum distance vertex from the set of vertices not 
		// yet processed. u is always equal to src in the first iteration. 
		int u = minDistance(dist, sptSet); 

		// Mark the picked vertex as processed 
		sptSet[u] = true; 
	
		// Update dist value of the adjacent vertices of the picked vertex. 
		for (int v = 0; v <= V; v++) 

		    // Update dist[v] only if is not in sptSet, there is an edge from 
		    // u to v, and total weight of path from src to v through u is 
		    // smaller than current value of dist[v] 
		    if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
			    && dist[u]+graph[u][v] < dist[v]) {							
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v]; 
		    }
    } 
    // print the constructed distance array 
    //printSolution(dist, V); 
} 


int main() 
{ 
    int i = 0, j = 0;
    
    int terminal_vertices[K] = {1,6,3};	
    int remaining_vertices[K] = {0};
    int source_vertex = 0;
    int is_processed[V] = {0};
    int is_added[V][V] = {0};
    int is_included[V][V] = {0};
    int total_cost = 0, count = 0, cost = 0, x = 0;

    int graph[V][V] = {
		                {0,0,0,0,0,0,0},
		                {0,0,7,0,0,0,6},
		                {0,7,0,1,0,0,5},
		                {0,0,1,0,1,3,0},
		                {0,0,0,1,0,1,4},
		                {0,0,0,3,1,0,10},
		                {0,6,5,0,4,10,0}						 
    		       };     
    
    /*
     * Step 1 of the algorithm
     * First Terminal Vertex is added to T
     * "Start with a subtree T consisting of 
     * one given terminal vertex"
     */
    printf("Terminal Vertex \"%d\" is added to T\n",terminal_vertices[0]);
    dijkstra(graph,terminal_vertices[0]);
    //printSolution(dist, V, terminal_vertices[0]); 
    is_processed[terminal_vertices[0]] = 1;
    T[0] = terminal_vertices[0];
    y++;
	    
    /*
     * Step 2 of the algorithm starts here
     * "While T does not span all terminals"
     */
    count = 1;
    while(count<K)
    {
	/*
	 * Step 2 a) of the algorithm 
	 * "Select a terminal x not in T that is closest 
         * to a vertex in T"
	 */		 		 
	x = 0;				/* x --> Next Terminal Vertex */
	int min = INT_MAX;
	
	for(i=1;i<K;i++)
	{
		if((min>dist[terminal_vertices[i]]) && 
		   (dist[terminal_vertices[i]] != 0) && 
		   ((is_processed[terminal_vertices[i]]) == 0))
	  	{
	 		min = dist[terminal_vertices[i]];
			x = terminal_vertices[i];		
		}
	} 		
	printf("Next Terminal Vertex to be added to T is : \"%d\" \n",x);
	/*printf("T ---> ");
 	for(i=0;i<y;i++)
	{
		printf("%d  ",T[i]);
	}*/

	/*
	 * Step 2 b) of the algorithm starts here 
	 * "Finding Vertex in T which is closest to 
	 * Next Terminal Vertex to be added" 
	 */
	//printf("\nStarted Processing T\n");
	int min_cost = INT_MAX;
	for(i=0;i<y;i++)
	{
		cost = 0;
		//printf("%d\n",T[i]);
		dijkstra(graph,T[i]);					
		//printSolution(dist, V, T[i]); 
		d = 0;
		find_parent(parent, x);
		/*printf("a ---> ");
	    	for(j=0;j<d;j++)
		{
		 	printf("%d  ",a[j]);        			 	
		}		
		printf("\n");*/

   	    	for(j=0;j<d;j++)
		{
			if(j == 0)
			{
				if(is_added[T[i]][a[0]] == 0)
				{
					is_added[T[i]][a[0]] = 1;
					//printf("Edge %d -> %d is considered\n",T[i],a[0]);
					cost += graph[T[i]][a[0]];
				}				
			}
			else
			{
				if(is_added[a[j-1]][a[j]] == 0)
				{
					is_added[a[j-1]][a[j]] = 1;
					//printf("Edge %d -> %d is considered\n",a[j-1],a[j]);
					cost += graph[a[j-1]][a[j]];
				}
			}				
		}	    	   
		if(cost < min_cost)
		{
			min_cost = cost;
			source_vertex = T[i];
		}
		/*printf("Source Vertex : %d\n",T[i]);
		printf("Cost : %d\n",cost);*/
		for(int l=0;l<V;l++)
		{
			for(int m=0;m<V;m++)
			{
				is_added[l][m] = is_included[l][m];
			}
		}				
	}
	/*printf("Ended Processing T\n");
	printf("Closest Source Vertex : %d\n",source_vertex);
	printf("Minimum Cost : %d\n",cost);*/
			
	/*
	 * x is connected with "source_vertex" in T
	 * "Adding to T the shortest path that connects x with T"
	 * Total Cost is calculated here
	 */		
	dijkstra(graph,source_vertex);					
	//printSolution(dist, V, source_vertex); 
		
	d = 0;
	find_parent(parent, x);
	/*printf("a ---> ");
	for(j=0;j<d;j++)
	{
	 	printf("%d  ",a[j]);        			 	
	}		
	printf("\n");*/
   	for(j=0;j<d;j++)
	{
		if(j==0)
		{
			if(is_included[source_vertex][a[0]] == 0)
			{
				is_included[source_vertex][a[0]] = 1;
				total_cost += graph[source_vertex][a[0]];
				//printf("Edge %d\t%d is added\n",source_vertex,a[0]);						
				if(is_processed[a[0]] == 0)
				{
 					is_processed[a[0]] = 1;
					T[y] = a[0];
					y++;
				}
			}				
		}
		else
		{
			if(is_included[a[j-1]][a[j]] == 0)
			{
				is_included[a[j-1]][a[j]] = 1;
				total_cost += graph[a[j-1]][a[j]];
				//printf("Edge %d\t%d is added\n",a[j-1],a[j]);
				if(is_processed[a[j-1]] == 0)
				{						
					is_processed[a[j-1]] = 1;
					T[y] = a[j-1];
					y++;
				}
				if(is_processed[a[j]] == 0)
				{
					is_processed[a[j]] = 1;
					T[y] = a[j];
					y++;
				}
			}
		}				
	}				   
	count++;
    }    
    
    for(i=0;i<y;i++)
    {
	    printf("Vertex %d is present in T\n",T[i]);
    }
	
    for(i=0;i<V;i++)
    {
	for(j=0;j<V;j++)
	{
		if(is_included[i][j] == 1)
		{
			printf("Edge %d <-> %d is in T\n",i,j);
		}
	}
    }
    printf("Total Cost : %d\n",total_cost);
    return 0; 
}


