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

int graph[100][100];
int vertices;
int visited[100];
int result_cycle;
int best;
int actual_vertex;

void DFS(int vertex){
  visited[vertex] = 1;
  if(result_cycle >= best){
    return;
  }
  for(int i=0; i < vertices; i++){
    if(graph[vertex][i]){
      if(i == actual_vertex){
        if(result_cycle < best){
          best = result_cycle;
          return;
        }
      }
      if(!visited[i]){
        result_cycle ++;
        DFS(i);
        result_cycle --;
        visited[i] = 0;
      }
    }
  }
}

int main(){
  int value;
  best =  9999999;
  scanf("%d",&vertices);
  for(int i=0;i<vertices; i++){
    for(int j=0;j<vertices; j++){
      scanf("%d", &value);
      graph[i][j] = value;
    }
  }

  for(int i=0;i<vertices; i++){
    for(int j=0;j<vertices; j++){
      visited[j] = 0;
    }
    result_cycle ++;
    actual_vertex = i;
    DFS(i);
    result_cycle = 0;
  }

  cout << best << endl;

  return 0;
}
