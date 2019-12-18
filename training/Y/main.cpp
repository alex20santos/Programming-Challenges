#include<iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <math.h>
#include <list>
using namespace std;


int nnodes;
vector<int> * graph;
vector<int> initial_costs;
vector<int> new_costs;
vector<int> visited;
int biggest;
int smallest_depth;

void BFS(int source){
  queue<int> tovisit;
  queue<int> depth;

  visited[source] = 1;
  tovisit.push(source);
  depth.push(source);

  int curr_node;
  int aux, actual_depth;

  while(!tovisit.empty()){
    curr_node = tovisit.front();
    actual_depth = depth.front();
    tovisit.pop();
    depth.pop();

    if(new_costs[curr_node] < biggest ){
      smallest_depth = actual_depth;
      biggest = new_costs[curr_node];
    }

    for(int i = 0 ; i < (int)graph[curr_node].size(); i++){
      aux = graph[curr_node][i];
      if(!visited[aux]){
        visited[aux] = 1;
        tovisit.push(aux);
        depth.push(actual_depth + 1);
      }
    }
  }
}



int main(){
  int cost, num ,to;
  bool threats;
  while(scanf("%d", &nnodes)!=EOF){
    threats=false;
    graph = new vector<int>[nnodes];
    visited = vector<int>(nnodes);
    for(int i=0;i<nnodes; i++){
      scanf("%d",&cost);

      initial_costs.push_back(cost);
      scanf("%d", &num);
      for(int j=0;j<num;j++){
        scanf("%d", &to );
        graph[i].push_back(to-1);
      }
    }
    for(int i=0; i<nnodes; i++){
      int sum = initial_costs[i];
      for(int j=0; j<(int)graph[i].size(); j++){
        sum += initial_costs[graph[i][j]];
      }
      new_costs.push_back(sum);
      if(sum < 0){
        threats = true;
      }
    }
    if(!threats){
      cout << "No threats!" << endl;
    }
    else{
      biggest = 9999999;
      smallest_depth = 9999999;
      BFS(0);
      initial_costs.clear();
      new_costs.clear();

      if(smallest_depth != 9999999){
        cout << smallest_depth << endl;
      }
      else{
        cout << "No threats!"  << endl;
      }
    }

  }

  return 0;
}
