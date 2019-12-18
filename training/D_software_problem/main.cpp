#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define UNVISITED 0

using namespace std;

class Vertex {
public:
    Vertex(int value) : value(value){}
    int value;
    int low;
    bool onStack;
    int scc_num;
    vector<int> neighbors;
    vector<int> items;
};

vector<Vertex> graph, sccs;
int num_vert;
stack<int> s;
queue<int> q;
bool * visited_scc;
int id,scc_count;
int *ids;
vector<int> result; //guarda o index do scc


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
        int sum = graph[n].value;
        Vertex v = Vertex(sum);
        v.items.push_back(n);
        //cout << n+1 << " ";
        s.pop();
        graph[n].onStack = false;
        graph[n].low = ids[index];
        graph[n].scc_num =scc_count;
        while(index != n){
            n = s.top();
            //cout << n+1 << " ";
            v.items.push_back(n);
            s.pop();
            graph[n].onStack = false;
            graph[n].low = curr->low;
            sum += graph[n].value;
            graph[n].scc_num =scc_count;
        }
        v.value = sum;
        sccs.push_back(v);
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
  visited_scc[index] = true;
  for(int i = 0; i <(int)curr.neighbors.size();i++){
      if(!visited_scc[curr.neighbors[i]]){
          dfs_sccs(curr.neighbors[i]);
      }
  }
}


void top_dfs(int index){
    Vertex *curr = &sccs[index];
    curr->onStack = true;
    vector<int> neigh = curr->neighbors;
    for(int i = 0; i < (int)neigh.size(); i++){
        if(!sccs[neigh[i]].onStack){
            top_dfs(neigh[i]);
        }
    }
    q.push(index);
}

void top_sort(){
    for(int i = 0; i < scc_count; i++){
        if(!sccs[i].onStack){
            top_dfs(i);
        }
    }
    while(!q.empty()){
        result.push_back(q.front());
        q.pop();
    }
}

int main(){
  int src,dest;
  scanf("%d",&num_vert);
  for (int i = 0; i < num_vert; i++) {
      graph.push_back(Vertex(1));
      graph[i].onStack = false;
      graph[i].low = 0;
  }
  for(int i=0;i<num_vert; i++){
    scanf("%d",&src);
    while(1){
      scanf("%d", &dest);
      if(dest==0){
        break;
      }
      else{
        graph[src-1].neighbors.push_back(dest-1);
      }
    }
  }
  id = 1;
  ids = new int[num_vert]();

  findSCCs();


  for(int i = 0; i < num_vert;i++){
      Vertex curr = graph[i];
      // cria as ligações dos sccs
      for(int j = 0;j < (int)curr.neighbors.size();j++){
        if(graph[curr.neighbors[j]].scc_num != curr.scc_num){
              sccs[curr.scc_num].neighbors.push_back(graph[curr.neighbors[j]].scc_num);
              // inverter ligação
          }
      }
  }

  top_sort();

  for(int i=0;i<(int)result.size(); i++){
    cout << "Stage "<< i+1 << ":" << endl;
    int actual = result[i];
    sort(sccs[actual].items.begin(),sccs[actual].items.end());
    for(int j=0;j<(int)sccs[actual].items.size();j++){
      if(j != (int)sccs[actual].items.size()-1){
        cout << sccs[actual].items[j]+1 <<  " ";
      }
      else{
        cout << sccs[actual].items[j]+1 << "\n";
      }
    }
  }
  return 0;
}
