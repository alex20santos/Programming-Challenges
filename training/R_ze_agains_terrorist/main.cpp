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
#include<algorithm>
using namespace std;

vector<int> * graph;
vector<int> low;
vector<int> dfs;
vector<int> used;
int sol;

vector<int> parent;
int nnodes;
int d_time;


vector<vector<int> > init_matrix(int m, int n){
	vector<vector<int> > matrix(m, vector<int>(n,0));
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

			if(dfs[vertex] == 1 && dfs[aux] != 2 && !used[vertex]){
		     sol = max(sol,(int)graph[vertex].size());
				 used[vertex] = 1;
			}
			if(dfs[vertex] != 1 && low[aux] >= dfs[vertex] && !used[vertex]){
			 sol = max(sol,(int)graph[vertex].size());
			 used[vertex] = 1;
			}

    }
    else if(parent[vertex] != aux){
      low[vertex] = min(low[vertex], dfs[aux]);
    }
  }
}


void reset(){
	graph = new vector<int>[nnodes];
	low = vector<int> (nnodes,0);
	dfs = vector<int> (nnodes,-1);
	parent = vector<int> (nnodes,-1);
	used = vector<int> (nnodes,0);
	sol = 0 ;
	d_time = 0;
}


int main(){
	int num,to;
	while(scanf("%d",&nnodes) != EOF){
		reset();
		for(int i=0;i<nnodes; i++){
			scanf("%d",&num);
			for(int j=0;j<num; j++){
				scanf("%d",&to);
				graph[i].push_back(to-1);
			}
		}
		for(int i = 0; i < nnodes; i++){
      if(dfs[i] == -1){ // not visited
        ART(i);
      }
    }
		if(sol == 0){
			cout << "Strong network" << endl;
		}
		else{
			cout << sol << endl;
		}
	}



  return 0;
}
