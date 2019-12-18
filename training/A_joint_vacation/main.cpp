#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define DEBUGe


vector<vector<int> >  graph;
int finish_place = -1;
int n =-1;

vector<vector<int> > init_graph(int n){
  vector<vector<int> > m(n,vector<int>(n));
  return m;
}

int print_graph() {
   for (int i = 0; i < (int)graph.size(); i++){
     for(int j=0; j< (int)graph[i].size(); j++){
       cout << graph[i][j] << endl;
     }
     cout << endl;
   }
   return 0;
}

int min_distance(int dist[], bool sptSet[])
{
   // Initialize min value
   int min = 900000;
   int min_index;

   for (int v = 0; v < n; v++)
     if (sptSet[v] == false && dist[v] <= min){
      min = dist[v];
      min_index = v;
     }

   return min_index;
}

void printSolution(int dist[])
{
    cout <<  dist[finish_place] << endl;
}

void dijkstra(){
  int dist[n];
  bool sptSet[n];
  for (int i = 0; i < n; i++){
    dist[i] = INT_MAX;
    sptSet[i] = false;
  }
  dist[0] = 0;

  for (int count = 0; count < n-1; count++) {

    int u = min_distance(dist, sptSet);

    sptSet[u] = true;

    if(finish_place == u)
      break;

    for (int v = 0; v < n; v++) {
      if (!sptSet[v] && graph[u][v]>0 && dist[u] != INT_MAX  && dist[u]+graph[u][v] < dist[v]){
        dist[v] = dist[u] + graph[u][v];
      }
    }
  }
  printSolution(dist);
}

int main() {
  int value;

  scanf("%d",&n);
  scanf("%d",&finish_place);
  finish_place = finish_place-1;
  graph = init_graph(n);
  for(int i=0;i<n;i++){
    scanf("%d",&value);
    for(int j=0;j<n;j++){
      scanf("%d",&value);
      graph[i][j] = value;
    }
  }
  dijkstra();
  return 0;
}
