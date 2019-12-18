#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#define UNVISITED 0

using namespace std;

class Vertex {
public:
    Vertex(int valaue) : value(value){}
    int value;
    int low;
    bool onStack;
    int scc_num;
    vector<int> neighbors;
};

int count_stores;
vector<Vertex> graph, sccs;
int num_vert;
stack<int> s;
queue<int> q;
bool * visited_scc;
int id,scc_count;
int *ids;

void dfs(int index){
    Vertex * curr = &graph[index];
    ids[index] = curr->low = id++;
    s.push(index);
    curr->onStack = true;
    for(int i = 0; i < (int)curr->neighbors.size();i++){
        if(ids[curr->neighbors[i]] == UNVISITED){
            dfs(curr->neighbors[i]);
        }
        if(graph[curr->neighbors[i]].onStack){
            curr->low = ((curr->low < graph[curr->neighbors[i]].low) ? curr->low:graph[curr->neighbors[i]].low);
        }
    }
    if(curr->low == ids[index]){
        int n = s.top();
        //cout << n << " ";
        s.pop();
        graph[n].onStack = false;
        graph[n].low = ids[index];
        graph[n].scc_num =scc_count;
        int sum = graph[n].value;
        while(index != n){
            n = s.top();
            //cout << n << " ";
            s.pop();
            graph[n].onStack = false;
            graph[n].low = curr->low;
            sum += graph[n].value;
            graph[n].scc_num =scc_count;
        }
        sccs.push_back(Vertex(sum));
        scc_count++;
        //cout<<  " scc created w/ sum "<< sum ;
        //cout << "\n";
    }
}

int findSCCs(){
    for(int i = 0; i < num_vert;i++){
        if(ids[i] == UNVISITED) {
            dfs(i);
        }
    }
    return 1;
}

void dfs_sccs(int index){
  Vertex curr = sccs[index];
  //cout << index << " " ;
  count_stores ++;
  visited_scc[index] = true;
  for(int i = 0; i <(int)curr.neighbors.size();i++){
      if(!visited_scc[curr.neighbors[i]]){
          dfs_sccs(curr.neighbors[i]);
      }
  }
}


int main(){
  int stores_conn;
  int solution=0;
  scanf("%d %d",&num_vert,&stores_conn);
  for (int i = 0; i < num_vert; i++) {
      graph.push_back(Vertex(1));
      graph[i].onStack = false;
      graph[i].low = 0;
  }
  for(int i=0;i<stores_conn; i++){
    int src, dest;
    scanf("%d %d",&src,&dest);
    graph[src-1].neighbors.push_back(dest-1);
  }
  id = 1;
  ids = new int[num_vert]();

  findSCCs();


  for(int i = 0; i < num_vert;i++){
      Vertex curr = graph[i];
      // cria as ligações dos sccs
      for(int j = 0;j < (int)curr.neighbors.size();j++){
        if(graph[curr.neighbors[j]].scc_num != curr.scc_num){
              sccs[graph[curr.neighbors[j]].scc_num].neighbors.push_back(curr.scc_num);
          }
      }
  }

  for(int i=0;i<(int)sccs.size(); i++){
    visited_scc = (bool *)malloc ((int)sccs.size() * sizeof (bool *));
    memset(visited_scc,false,(int)sccs.size()*sizeof(bool));
    count_stores = 0;
    dfs_sccs(i);
    if(count_stores == (int)sccs.size()){
      solution += sccs[i].value;
    }
  }

  cout << solution << endl;

  return 0;
}
