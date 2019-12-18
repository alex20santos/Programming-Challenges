#include<iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#define NODEBUG
using namespace std;

vector<int> * graph; // lista de adjacencia
vector<int> low;
vector<int> dfs;
vector<int> parent;
vector<int> used;

vector< pair<int,int> > sol;
int npositions, nroads;
int d_time;

void reset(){
  for(int i = 0; i < npositions; i++){
    dfs[i] = -1;
    parent[i] = -1;
  }
}

void ART(int vertex){
  low[vertex] = dfs[vertex] = d_time = d_time+1;
  for(int i = 0; i < (int)graph[vertex].size(); i++){
    int aux = graph[vertex][i];
    if(dfs[aux] == -1){
      parent[aux] = vertex;
      ART(aux);
      low[vertex] = min(low[vertex],low[aux]);

      if(low[aux] > dfs[vertex]){ // se for verdade é uma bridge entre aux e vertex
        pair<int, int> p;
        if(aux < vertex){
          p = make_pair(aux,vertex);
        }
        else{
          p = make_pair(vertex,aux);
        }
        sol.push_back(p);
      }

    }
    else if(parent[vertex] != aux){
      low[vertex] = min(low[vertex], dfs[aux]);
    }
  }
}

bool compare(pair<int,int> p1, pair<int,int> p2){
  if(p1.first < p2.first){
    return true;
  }
  if(p1.first > p2.first){
    return false;
  }
  if(p1.second < p2.second){
    return true;
  }
  return false;
}

int main(){
  int p1, p2;
  while(scanf("%d %d", &npositions, &nroads) != EOF){
    graph = new vector<int>[npositions];
    low = vector<int> (npositions,0);
    used = vector<int> (npositions,0);
    parent = vector<int> (npositions,-1);
    dfs = vector<int> (npositions,-1);
    reset();
    for(int i = 0; i < nroads; i++){
      scanf("%d %d",&p1,&p2);
      graph[p1].push_back(p2);
      graph[p2].push_back(p1);
    }
    for(int i = 0; i < npositions; i++){
      if(dfs[i] == -1){
        ART(i);
      }
    }
    sort(sol.begin(), sol.end(), compare);
    if((int)sol.size() == 0){
      printf("No road\n");
    }
    else{
      for(int i = 0; i < (int) sol.size(); i++){
        printf("%d %d\n",sol[i].first,sol[i].second);
      }
      sol.clear();
    }
  }
  return 0;
}
