#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;

int nfunctions;
int graph[100][101];
int visited[100];
vector<int> recursive;
int actual_function;
bool to_leave;

void BFS(int function){
  queue<int> tovisit;
  visited[function] = 1;
  tovisit.push(function);
  int curr_function;
  int aux;
  //cout << "BFS for " << function << endl;
  while(!tovisit.empty()){
    curr_function = tovisit.front();
    //cout << curr_function << " -> current " << endl;;
    tovisit.pop();

    for(int i = 1; i <= graph[curr_function][0]; i++){
      aux = graph[curr_function][i];

      //cout << function << " " << graph[curr_function][i] << endl;;

      if(aux == function){
        recursive.push_back(aux);
        return;
      }
      if(!visited[aux]){
        visited[aux] = 1;
        tovisit.push(aux);
      }
    }
  }
}


void DFS(int function){
  if(to_leave){
    return;
  }
  visited[function] = 1;
	//cout << function << endl;
  //cout << function << " " << graph[curr_function][i] << endl;;

  for(int i = 1; i <= graph[function][0]; i++){
    if(to_leave){
      return;
    }
    int aux = graph[function][i];
    //cout << "aux " << aux << " " << actual_function << endl;
    if(aux == actual_function){
      recursive.push_back(actual_function);
      to_leave = true;
      return;
    }
    if(!visited[aux]){
			DFS(aux);
		}
	}
}

int main(){
  scanf("%d",&nfunctions);
  for(int i = 0; i < nfunctions; i++){
    scanf("%d",&graph[i][0]);
    for(int j = 1; j <= graph[i][0]; j++){
      scanf("%d",&graph[i][j]);
    }
  }
  for(int i = 0; i < nfunctions; i++){
      for(int j = 0; j < nfunctions; j++){
        visited[j] = 0;
      }
      BFS(i);
  }


  /**** Com DFS ****/
  /*for(int i = 0; i < nfunctions; i++){
      for(int j = 0; j < nfunctions; j++){
        visited[j] = 0;
      }
      to_leave = false;
      actual_function = i;
      //cout << "DFS for " << i << endl;
      DFS(i);
  }*/

  sort(recursive.begin(),recursive.end());
  for(int i = 0; i < (int) recursive.size(); i++){
    printf("%d\n",recursive[i]);
  }
  return 0;
}
