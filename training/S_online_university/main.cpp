#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

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
};
int global_max;

vector<Vertex> vertexes,sccs;
int n_classes;
stack<int> s;
queue<int> q;
int id,scc_count;
int *ids;

void dfs(int index){
    Vertex* curr = &(vertexes[index]);
    ids[index] = curr->low = id++;
    s.push(index);
    curr->onStack = true;
    vector<int> neighbors = curr->neighbors;
    for(int i = 0; i < (int)neighbors.size();i++){
        if(ids[neighbors[i]] == UNVISITED){
            dfs(neighbors[i]);
        }
        if(vertexes[neighbors[i]].onStack){
            curr->low = ((curr->low < vertexes[neighbors[i]].low) ? curr->low:vertexes[neighbors[i]].low);
        }
    }
    if(curr->low == ids[index]){
        int n = s.top();
        s.pop();
        vertexes[n].onStack = false;
        vertexes[n].low = ids[index];
        vertexes[n].scc_num =scc_count;
        int sum = vertexes[n].value;
        while(index != n){
            n = s.top();
            s.pop();
            vertexes[n].onStack = false;
            vertexes[n].low = curr->low;
            sum += vertexes[n].value;
            vertexes[n].scc_num =scc_count;
        }
        sccs.push_back(Vertex(sum));
        scc_count++;
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
    vector<int> result; //guarda o index do scc
    int max;
    for(int i = 0; i < scc_count; i++){
        if(!sccs[i].onStack){
            top_dfs(i);
        }
    }
    while(!q.empty()){
        result.push_back(q.front());
        q.pop();
    }
    for(int i = 0; i < scc_count; i++) {
        Vertex *cur = &sccs[result[i]]; // iterar todos os resultados em ordem topologica
        vector<int> req = cur->neighbors;
        max = 0;

        /*
         * procura o max dos requisitos para calcular o valor do no;
         * */
        for(int r = 0; r < (int)req.size();r++){
            if(sccs[req[r]].value > max){
                max = sccs[req[r]].value;
            }
        }
        cur->value = max + cur->value;

    }
    max = 0;
    for(int i = 1; i < scc_count; i++){
        Vertex *cur = &sccs[result[i]]; // iterar todos os resultados em ordem topologica
        if(cur->value > max)
            max = cur->value;
    }
    printf("%d\n",max);

}

int findSCCs(){
    for(int i = 0; i < n_classes;i++){
        if(ids[i] == UNVISITED) {
            dfs(i);
        }
    }
    return 1;
}



bool searchNeighbor(vector<int> list, int n){
    for(int i =0; i < (int)list.size();i++){
        if(list[i] == n){
            return true;
        }
    }
    return false;
}



int main(){
    int n_tests,n_req,value;

    cin >> n_tests;
    vertexes = vector<Vertex>();
    sccs = vector<Vertex>();
    s = stack<int>();
    for(int k = 0; k < n_tests;k++) {
        global_max = 0;
        scc_count = 0;
        vertexes.clear();
        sccs.clear();
        cin >> n_classes >> n_req;
        id = 1;
        ids = new int[n_classes]();

        for (int i = 0; i < n_classes; i++) {
            cin >> value;
            vertexes.push_back(Vertex(value));
            vertexes[i].onStack = false;
            vertexes[i].low = 0;
        }
        for (int i = 0; i < n_req; i++) {
            int src, dest;
            cin >> src >> dest;
            vertexes[dest-1].neighbors.push_back(src-1);
        }


        findSCCs();

        for(int i = 0; i < n_classes;i++){
            Vertex* curr = & vertexes[i];
            vector<int> neigh = curr->neighbors;
            // cria as ligações dos sccs
            for(int j = 0;j < (int)neigh.size();j++){
                if(vertexes[neigh[j]].scc_num != curr->scc_num){
                    sccs[curr->scc_num].neighbors.push_back(vertexes[neigh[j]].scc_num);
                }
            }
        }
        s = stack<int>();
        q = queue<int>();
        top_sort();

    }

    return 0;
}
