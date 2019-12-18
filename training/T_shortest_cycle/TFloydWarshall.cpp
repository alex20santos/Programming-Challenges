#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

#define INF 99999


int graph[100][100];
int dist[100][100];
int nnodes;
int vertex;
int globlal;
int best;
bool vis[100];

void floydWarshall (int V) 
{ 
    /* dist[][] will be the output matrix that will finally have the shortest  
      distances between every pair of vertices */
    int i, j, k; 
  
    /* Initialize the solution matrix same as input graph matrix. Or  
       we can say the initial values of shortest distances are based 
       on shortest paths considering no intermediate vertex. */
    for (i = 0; i < V; i++) 
        for (j = 0; j < V; j++) 
            dist[i][j] = graph[i][j]; 

  
    /* Add all vertices one by one to the set of intermediate vertices. 
      ---> Before start of an iteration, we have shortest distances between all 
      pairs of vertices such that the shortest distances consider only the 
      vertices in set {0, 1, 2, .. k-1} as intermediate vertices. 
      ----> After the end of an iteration, vertex no. k is added to the set of 
      intermediate vertices and the set becomes {0, 1, 2, .. k} */
    for (k = 0; k < V; k++) 
    { 
        // Pick all vertices as source one by one 
        for (i = 0; i < V; i++) 
        { 
            // Pick all vertices as destination for the 
            // above picked source 
            for (j = 0; j < V; j++) 
            { 
                // If vertex k is on the shortest path from 
                // i to j, then update the value of dist[i][j] 
                if (dist[i][k] + dist[k][j] < dist[i][j]) 
                    dist[i][j] = dist[i][k] + dist[k][j]; 
            } 
        } 
    } 
} 

void shcycle(){
    globlal = 9999;

    floydWarshall(nnodes);

    for (int i = 0; i < nnodes; i++){
        for(int j = 0; j< nnodes; j++){
            if(i==j && (globlal > dist[i][j])){
                globlal = dist[i][j];
            }
        }
    }

}

int main(){
    int t;

    scanf("%d",&nnodes);

    for (int i = 0; i < nnodes; i++){
        for (int j = 0; j < nnodes; j++){
            graph[i][j] = INF;
        }
    }

    for (int i = 0; i < nnodes; i++){
        for (int j = 0; j < nnodes; j++){
            scanf("%d",&t);
            if(t != 0)
                graph[i][j] = t;
        }
    }

    shcycle();

    cout << globlal  << "\n"; 

    return 0;
}