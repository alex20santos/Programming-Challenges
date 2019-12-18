#include<iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

int n_vertices;
int **graph;
int **dist;

void printSolution(){
    for (int i = 0; i < n_vertices; i++)
    {
        for (int j = 0; j < n_vertices; j++)
        {
            if (dist[i][j] == -1)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}



void floydWarshall(){
    int i, j, k;

    for (i = 0; i < n_vertices; i++) {
        for (j = 0; j < n_vertices; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    for (k = 0; k < n_vertices; k++){
        // Pick all vertices as source one by one
        for (i = 0; i < n_vertices; i++){
            // Pick all vertices as destination for the
            // above picked source
            for (j = 0; j < n_vertices; j++){
                // If vertex k is on the shortest path from
                // i to j, then update the value of dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    //printSolution();
}


int main(){
    int value, from, to, n_tranformations, n_queries;
    scanf("%d", &n_vertices);

    graph = (int **)malloc (n_vertices * sizeof (int *));
    for (int i = 0; i < n_vertices; ++i)
        graph[i] = (int *) malloc (n_vertices * sizeof (int));

    scanf("%d", &n_tranformations);

    for(int i=0; i< n_vertices; i++){
      for(int j=0; j< n_vertices; j++){
        graph[i][j] = 999999999;
      }
    }

    for(int i=0;i< n_tranformations; i++){
      scanf("%d %d %d",&from, &to, &value);
      graph[from-1][to-1] = value;
    }


    dist = (int **)malloc (n_vertices * sizeof (int *));
    for (int i = 0; i < n_vertices; ++i)
        dist[i] = (int *) malloc (n_vertices * sizeof (int));

    floydWarshall();

    scanf("%d",&n_queries );
    for(int i=0; i< n_queries; i++){
      scanf("%d %d", &from, &to);
      if(dist[from-1][to-1]!=999999999)
        cout << dist[from-1][to-1] << endl;
      else{
        cout << "Impossible!" << endl;
      }
    }

    return 0;
}
