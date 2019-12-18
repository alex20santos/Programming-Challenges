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
vector<bool> used;
vector<vector<int> > values_matrix;
vector<int> sol;

vector<int> parent;
int ncities;
int d_time;
int solution;


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

			if(dfs[vertex] == 1 && dfs[aux] != 2){
			 sol.push_back(vertex);

			}
			if(dfs[vertex] != 1 && low[aux] >= dfs[vertex]){
				sol.push_back(vertex);
			}
						
    }
    else if(parent[vertex] != aux){
      low[vertex] = min(low[vertex], dfs[aux]);
    }
  }
}


void print_solution(){
	int best = 0;
	for(int i=0; i<(int)sol.size();i++){
		int actual_max=0;
		for(int j=0;j<(int)graph[sol[i]].size();j++){
			int actual = graph[sol[i]][j];
			actual_max += values_matrix[actual][sol[i]];
		}
		if(actual_max > best){
			best = actual_max;
		}
	}
	cout << best << endl;
}

void reset(){
	graph = new vector<int>[ncities];
	values_matrix = init_matrix(ncities,ncities);
	low = vector<int> (ncities,0);
	dfs = vector<int> (ncities,-1);
	parent = vector<int> (ncities,-1);
	used = vector<bool> (ncities,false);
	sol = vector<int>();
	d_time = 0;
}


int main(){
	int num,to, value;
	while(scanf("%d",&ncities) != EOF){
		reset();
		for(int i=0;i<ncities; i++){
			scanf("%d",&num);
			for(int j=0;j< num; j++){
				scanf("%d",&to);
				scanf("%d",&value);
				graph[i].push_back(to-1);
				values_matrix[i][to-1] = value;
			}
		}
		/*for(int i = 0; i < ncities; i++){
			for(int j=0; j< graph[i].size(); j++){
				cout << graph[i][j]+1 << " ";
			}
			cout << endl;
		}*/
		for(int i = 0; i < ncities; i++){
      if(dfs[i] == -1){ // not visited
        ART(i);
      }
    }
		if((int)sol.size()==0){
			cout << "Well designed city!" << endl;
		}
		else{
			print_solution();
		}
	}



  return 0;
}
