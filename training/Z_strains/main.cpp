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

/*

Encontrar grafos disconexos
*/

using namespace std;

int m,n;
vector<vector<int> >  graph; //lista de adjacencia
int result;
vector<vector< int > >  matrix;



vector<vector<int> > init_matrix(int m, int n){
	vector<vector<int> > matrix(m, vector<int>(n,-1));
	return matrix;
}


void create_graph(){
  int conn;
  int actual;
  for(int i=0; i<m; i++){
    for(int j=0;j<n; j++){
        actual = matrix[i][j];
        if(matrix[i][j] >= 0){
          if(i-1>=0 && j-1>=0 && i-1<m && j<n){
            if( matrix[i-1][j-1] >= 0){
              conn = matrix[i-1][j-1];
			  			graph[actual].push_back(conn);
            }
          }
          if(i-1>=0 && j>=0 && i-1<m && j<n){
            if( matrix[i-1][j] >= 0){
              conn = matrix[i-1][j];
			  			graph[actual].push_back(conn);
            }
          }
          if(i-1>=0 && j+1>=0 && i-1<m && j+1<n){
            if(matrix[i-1][j+1] >= 0){
              conn = matrix[i-1][j+1];
			  			graph[actual].push_back(conn);
            }
          }
          if (i>=0 && j-1>=0 && i<m && j-1<n) {
            if( matrix[i][j-1] >= 0){
              conn = matrix[i][j-1];
			  			graph[actual].push_back(conn);
            }
          }
          if(i>=0 && j+1>=0 && i<m && j+1<n){
            if( matrix[i][j+1] >= 0){
              conn = matrix[i][j+1];
			  			graph[actual].push_back(conn);
            }
          }
          if(i+1 >= 0 && j-1 >= 0 && i+1 < m && j-1<n){
            if(matrix[i+1][j-1] >= 0){
              conn = matrix[i+1][j-1];
			  			graph[actual].push_back(conn);
            }
          }
          if(i+1>=0 && j>=0 && i+1<m && j<n){
            if( matrix[i+1][j] >= 0){
              conn = matrix[i+1][j];
			  			graph[actual].push_back(conn);
            }
          }
          if(i+1>=0 && j+1>=0  && i+1<m && j+1<n){
            if(matrix[i+1][j+1] >= 0){
              conn = matrix[i+1][j+1];
			  			graph[actual].push_back(conn);
            }
          }
        }
    }
  }
}

int zz;
void DFS(int vertex,bool visited[]){
	visited[vertex] = true;
	//cout << vertex << " " ;
	zz++;
  for(int i = 0; i < (int)graph[vertex].size(); ++i){
      if(!visited[graph[vertex][i]]){
				DFS(graph[vertex][i], visited);
			}
	}
}

void calculate_strains(){
	bool *visited = new bool[(int)graph.size()];
  for (int i = 0; i < (int)graph.size(); i++){
		visited[i] = false;
	}

	for (int v=0; v<(int)graph.size(); v++){
		if (visited[v] == false){
			//cout << "DFS for " << v << endl;
			DFS(v,visited);
			//cout << "\n";
			//cout << " tem " << zz << " elementos" << endl;
			zz = 0;
			result++;
		}
	}
}


int main(){
	char in_value;
	zz =0;
	scanf("%d",&m);
	scanf("%d",&n);
	matrix = init_matrix(m,n);
	int counter = 0;
	scanf("%c",&in_value);
	result = 0;
	for(int i=0; i < m; i++){
		for(int j=0;j<n; j++){
			scanf("%c",&in_value);
			if(in_value == '+'){
				matrix[i][j] = counter;
				counter++;
			}
		}
		scanf("%c",&in_value);
	}

	graph = init_matrix(counter,0);

	create_graph();

	calculate_strains();

	cout << result << endl;

	return 0;
}
