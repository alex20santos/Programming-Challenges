#include <string.h>
#include <cstdio>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <vector>
using namespace std;

#define INF INT_MAX;


struct Node{
    int cost;
    int node;
    Node(){}
    Node(int n, int c){node = n;cost = c;}
    bool operator <(const Node & node)const{
        return cost > node.cost;
    }
};


int graph[200][200];
int nnodes, target;

int min_distance(int dist[],bool visited[]){

    int min = 9999;
    int min_index;

    for(int i = 0; i < nnodes; i++){
        if(visited[i] == false && dist[i] <= min){
            min = dist[i];
            min_index = i;
        }
    }

    return min_index;

}


int dijkstra(int src){
    int dist[200];

    for(int i = 0; i < 200; i++){
        dist[i] = INF;
    }

    dist[src] = 0;

    priority_queue< Node > pq;

    pq.push(Node(0, 0));

    while(!pq.empty())
    {
        int from = pq.top().node;
        pq.pop();

        if(from == target)
            return dist[from];

        for(int i = 0; i < nnodes; i++){
            int to = i;
            int cost = graph[from][to];
            if(graph[from][to] > 0 && dist[to] > dist[from] + cost){
                dist[to] = dist[from] + cost;
                pq.push(Node(to,dist[to]));
            }
        }
    }

    return dist[target];

}


int main(){

    int aux;

    scanf("%d %d",&nnodes,&target);

    target--;

    for(int i = 0; i < nnodes; i++){
        scanf("%d",&aux);
        int aux1 = aux;
        aux1--;
        for (int j = 0; j < nnodes; j++){
            scanf("%d",&aux);
            graph[aux1][j] = aux;
        }
    }

    cout << dijkstra(0) << "\n";


    return 0;
}
