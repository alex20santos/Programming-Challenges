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

int n_swarms, n_techs,dist_r_t, dist_r_r;
vector<pair<int,int> > technicians;
vector<pair<int,int> > set;
vector<int> arr;
bool exit_dfs;
vector<bool> visited;
vector<vector<double> > saved_dist_r_r;
vector<vector<double> > saved_dist_r_t;
int num_elements;
vector<int> * adj;



vector<vector<double> > init_matrix(int m, int n){
	vector<vector<double> > matrix(m, vector<double>(n,-1.0));
	return matrix;
}


void union_values(int A, int B){
  int TEMP = arr[A];
  for(int i = 0; i < (int)arr.size();i++){
    if(arr[i] == TEMP){
				arr[i] = arr[B];
			}
    }
}

bool find(int A, int B){
	if(arr[A] == arr[B] ){
  	return true;
	}
	return false;
}

int distance_r_r(int A, int B){
	double res;
	if(saved_dist_r_r[A][B] != -1.0 || saved_dist_r_r[B][A] != -1.0){
		return saved_dist_r_r[A][B];
	}
	else{
		res = ((set[A].first - set[B].first)*(set[A].first - set[B].first) + (set[A].second - set[B].second)*(set[A].second - set[B].second) );
		saved_dist_r_r[A][B] = res;
		saved_dist_r_r[B][A] = res;
	}
	return res;
}

int distance_r_t(int A, int B){
	double res;
	if(saved_dist_r_t[A][B] != -1.0){
		return saved_dist_r_t[A][B];
	}
	else{
		res = ((set[A].first - technicians[B].first)*(set[A].first - technicians[B].first) + (set[A].second - technicians[B].second)*(set[A].second - technicians[B].second) );
		saved_dist_r_t[A][B] = res;
	}
	return res;
}


void reset(){
	dist_r_r = dist_r_r*dist_r_r;
	dist_r_t = dist_r_t*dist_r_t;
	arr = vector<int>(1000,-1);
	visited = vector<bool>();
	set = vector< pair<int,int> >();
	exit_dfs = false;
	technicians = vector< pair<int,int> >();
	saved_dist_r_r = init_matrix(1000,1000);
	saved_dist_r_t = init_matrix(1000,10);
	adj = new vector<int>[1000];
}


void make_conn(){
	for(int i=0; i<num_elements; i++){
		for(int j=i+1;j<num_elements; j++){
			if(!find(i,j)){
				if(distance_r_r(i,j)<=dist_r_r){
					union_values(i,j);
					break;
				}
			}
		}
	}
}

void DFS(int vertex){
	int k;
	visited[vertex] = true;
	cout << vertex << endl;
	if(exit_dfs){
		return;
	}
	for(k=0; k<(int)technicians.size(); k++){
		if(distance_r_t(vertex,k) <= dist_r_t){
			cout << "YES" << endl;
			exit_dfs = true;
			return;
		}
	}
  for(int i = 0; i < (int)adj[vertex].size(); i++){
		if(find(adj[vertex][i],vertex)){
			if(exit_dfs){
				return;
			}
	    if(!visited[adj[vertex][i]]){
				DFS(adj[vertex][i]);
			}
		}
	}
}

void set_neighbours(){
	for(int i=0;i<num_elements;i++){
		for(int j = 0; j <num_elements;j++){
			if(find(i,j) && i!=j){
				adj[i].push_back(j);
			}
		}
	}
}

bool check_for_techs(int init_robot){
	int TEMP = arr[init_robot];
	for(int i=1;i<(int)arr.size();i++){
		if(arr[i] == TEMP){
			for(int k=0; k<(int)technicians.size(); k++){
				if(distance_r_t(i,k) <= dist_r_t){
					cout << "YES" << endl;
					return true;
				}
			}
		}
	}
	return false;
}

int main(){
	int ncases, x_t, y_t, n_elements, x_e, y_e;
	scanf("%d", &ncases);
	for(int i=0; i< ncases; i++){
		scanf("%d %d %d %d", &n_swarms, &n_techs,&dist_r_r, &dist_r_t);
		reset();
		for(int j=0;j<n_techs; j++){
			scanf("%d %d", &x_t, &y_t );
			pair<int, int> p;
			p = make_pair(x_t,y_t);
			technicians.push_back(p);
		}
		int count = 0;
		for(int j=0;j<n_swarms; j++){
			scanf("%d", &n_elements);
			int first = count;
			for(int k=0;k<n_elements; k++){
				scanf("%d %d", &x_e, &y_e);
				pair<int, int> pe;
				pe = make_pair(x_e,y_e);
				set.push_back(pe);
				arr[count] = count;
				union_values(count,first);
				count ++;
			}
		}
		num_elements = count;
		make_conn();
		//set_neighbours();
		//visited = vector<bool>(num_elements,false);
		//DFS(0);
		if(!check_for_techs(0)){
			cout << "NO\n";
		}
		/*cout << "arr" << endl;
		for(int j=0;j<num_elements; j++){
			cout << arr[j] << " ";
		}
		cout << endl;*/
	}
	return 0;
}
