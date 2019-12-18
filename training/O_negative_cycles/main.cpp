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

#define MAX 9999999

struct Wormhole {
    int x, y, t;
};

vector<Wormhole> edges(100);
vector<int> dist(1000);
int cases, n_stars,n_wormholes;

void Bellman_Ford() {
    int i,j;
    for (i = 0; i < n_stars; i++) {
        dist[i] = MAX;
    }
    dist[0] = 0;

    for(i = 1; i <= n_stars -1;i++) {
        for(j = 0; j < n_wormholes; j++) {
            int u = edges[j].x;
            int v = edges[j].y;
            int weight = edges[j].t;

            if (dist[u] != MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    for(i = 0; i < n_wormholes; i++) {
        int u = edges[i].x;
        int v = edges[i].y;
        int weight = edges[i].t;

        if (dist[u] != MAX && dist[u] + weight < dist[v]) {
            cout << "possible" << endl;
            // ciclo negativo
            return;
        }
    }
    cout << "not possible" << endl;
    return;
}


int main() {
    int i,j;
    scanf("%d", &cases);
    for(i = 0; i < cases; i++) {
        scanf("%d %d",&n_stars,&n_wormholes);
        for(j = 0; j < n_wormholes; j++) {
            scanf("%d %d %d",&edges[j].x, &edges[j].y, &edges[j].t);
        }
        Bellman_Ford();
        dist.clear();
        edges.clear();
    }
    return 0;
}
