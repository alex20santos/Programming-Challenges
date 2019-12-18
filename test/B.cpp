#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#define MAX 99999
using namespace std;

struct Edge{
    int from, to, weight;
};

vector<Edge> edges(400);
vector<int> dist(20);

void Bellman_Ford(int source, int target, int vertex, int n_edges){
    int i, j;
    for(i = 0; i < vertex; i++){
        dist[i] = MAX;
    }
    dist[source - 1] = 0;
    for(i = 0; i < vertex; i++){
        for(j = 0; j < n_edges; j++){
            int u = edges[j].from;
            int v = edges[j].to;
            int peso = edges[j].weight;

            if(dist[u] != MAX && dist[u] + peso < dist[v]){
                dist[v] = dist[u] + peso;
            }
            //cout << "vertex " << i << endl;
            //cout << "from " << u << " to "<< v<< endl;

            /*for(int i=0;i<vertex;i++){
              cout << dist[i] << " ";
            }
            cout << endl;*/
        }
    }

    // If we iterate through all edges one more time and get a shorter path
    //for any vertex, then there is a negative weight cycle.

    for(i = 0; i < n_edges; i++){
        int u = edges[i].from;
        int v = edges[i].to;
        int peso = edges[i].weight;
        if(dist[u] != MAX && dist[u] + peso < dist[v]){
            cout << "Negative Cycle" << endl;
            return;
        }
    }

    cout << dist[target - 1] << endl;


    return;
}

int main()
{
    int count = 0, n_vertex, from, to, aux, i, j;
    scanf("%d %d %d", &n_vertex, &from, &to);
    for(i = 0; i < n_vertex; i++){
        for(j = 0; j < n_vertex; j++){
            scanf("%d", &aux);
            if(aux != 0){
                edges[count].from = i;
                edges[count].to = j;
                edges[count].weight = aux;
                count++;
            }
        }
    }
    Bellman_Ford(from, to, n_vertex, count);
    dist.clear();
    edges.clear();
    return 0;
}
