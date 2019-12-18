#include<iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;

int n_nodes;
vector<int> * graph;
int visited[800];
int best;
int solution;

void BFS(int node){
  queue<int> tovisit;
  queue<int> depth;
  visited[node] = 1;
  tovisit.push(node);
  depth.push(node);
  int curr;
  int aux;

  while(!tovisit.empty()){
    curr = tovisit.front();
    int actual_depth = depth.front();
    tovisit.pop();
    depth.pop();
    if((int)graph[curr].size() > best){
      best = (int)graph[curr].size();
      solution = actual_depth;
    }

    for(int i = 0; i < (int)graph[curr].size(); i++){
      aux = graph[curr][i];
      if(!visited[aux]){
        visited[aux] = 1;
        tovisit.push(aux);
        depth.push(actual_depth + 1);
      }
    }
  }
}




int main(){
  int links,link;
  while(scanf("%d", &n_nodes)!=EOF){
    graph = new vector<int>[n_nodes];
    for(int i = 0; i < n_nodes; i++){
      scanf("%d",&links);
      if(i==0){
        best = links;
      }
      for(int j = 0; j <links; j++){
        scanf("%d",&link);
        link--;
        graph[i].push_back(link);
      }
    }
    for(int j = 0; j < n_nodes; j++){
      visited[j] = 0;
    }

    BFS(0);
    if(best != (int)graph[0].size()){
      cout << solution << endl;
    }
    else{
      cout << "King of popularity!" << endl;
    }

  }

  return 0;
}
