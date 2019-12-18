#include<iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

vector<int> * graph;
vector<int> low;
vector<int> dfs;
vector<int> used;
vector<int> parent;

int nplaces;
int d_time;
int solution;


vector<vector<int> > init_matrix(int m, int n){
	vector<vector<int> > matrix(m, vector<int>(n,-1));
	return matrix;
}

void ART(int vertex){
  low[vertex] = dfs[vertex] = d_time = d_time+1; // atucalizar low e dfs com o descovery time
  for(int i = 0; i < (int)graph[vertex].size(); i++){ // os vizinhos
    int aux = graph[vertex][i];
    if(dfs[aux] == -1){ // se ainda não foi visitado
      parent[aux] = vertex;
      ART(aux);
      low[vertex] = min(low[vertex],low[aux]);

      if(((dfs[vertex] == 1 && dfs[aux]!= 2) || (dfs[vertex] != 1 && low[aux] >= dfs[vertex] )) && !used[vertex]){
        // articulation point
        //cout << "vertex: " << vertex  << endl;
				used[vertex] = true;
        solution++;
      }
    }
    else if(parent[vertex] != aux){
      low[vertex] = min(low[vertex], dfs[aux]);
    }
  }
}


int main(){
  int aux;
  while(1){
    scanf("%d",&nplaces);
    d_time = 0;
    solution = 0;
    graph = new vector<int>[nplaces]; // ou init_matrix com vector<vector<int> >
    low = vector<int> (nplaces,0);
    used = vector<int> (nplaces,0);
    dfs = vector<int> (nplaces,-1);
    parent = vector<int> (nplaces,-1);

    if(nplaces == 0){
      break;
    }
    while(1){
      scanf("%d",&aux);
      if(aux == 0){
        break;
      }
      string line;
      getline(cin,line);
      stringstream ss(line);
      int aux2;
      while(ss >> aux2){
        graph[aux-1].push_back(aux2-1);
        graph[aux2-1].push_back(aux-1);
      }
    }

    for(int i = 0; i < nplaces; i++){
      if(dfs[i] == -1 ){
        ART(i);
      }
    }
    cout << solution << endl;
  }
  return 0;
}
