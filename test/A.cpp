#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int n_vertices;
int **graph;
int **dist;

void floydWarshall() {
    int i,j,k;

    for(i = 0; i < n_vertices; i++) {
        for(j = 0; j < n_vertices;j++) {
            dist[i][j] = graph[i][j];
        }
    }

    for(k = 0; k < n_vertices;k++) {
        for(i = 0; i < n_vertices; i++) {
            for(j = 0; j < n_vertices; j++) {
                if(dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return;
}

int main()
{
    int i,n_edges,from,to,s,t;
    scanf("%d %d", &n_vertices,&n_edges);
    scanf("%d %d", &s,&t);

    graph = (int**) malloc(n_vertices * sizeof(int*));
    dist = (int**) malloc(n_vertices * sizeof(int*));

    for(i = 0; i < n_vertices; ++i) {
        graph[i] = (int*) malloc(n_vertices * sizeof(int));
    }

    for(i = 0; i < n_vertices; ++i) {
        dist[i] = (int*) malloc(n_vertices * sizeof(int));
    }

    for(i = 0; i < n_vertices; ++i) {
        for(int j = 0; j < n_vertices; ++j) {
            graph[i][j] = 99999999;
        }
    }

    for(i = 0; i < n_edges; ++i) {
        scanf("%d %d",&from, &to);
        graph[from-1][to-1] = 1;
    }


    floydWarshall();

    cout << dist[s-1][t-1] << endl;
    return 0;
}
