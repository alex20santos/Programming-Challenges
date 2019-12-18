#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>



using namespace std;
int nnodes;
int graph[21][21];
int low[21];
int dfs[21];
int used[21];
int parent[21];
vector<int> result;
int d_time;
int count_art;
int num_elements;
int visited[21];
int visit_node[21];

 void ART(int vertex){

    low[vertex] = dfs[vertex] = d_time = d_time +1 ;
    for(int i=0; i<nnodes; i++){
        if(graph[vertex][i] == 1){
            int aux = i;
            if(dfs[aux] == -1 ){
                //cout << " ->>> dfs de aux " << aux <<" " <<dfs[aux] << endl;

                ART(aux);
                low[vertex] = min(low[vertex], low[aux]);
                cout << "dfs de vertex "<<vertex<< " " << dfs[vertex] << endl;
                cout << "dfs de aux "<<aux<< " " << dfs[aux] << endl;

                if(((dfs[vertex] == 1 && dfs[aux]!=2) || (dfs[vertex] != 1 && low[aux] >= dfs[vertex])) && !used[vertex]){
                    cout << "AP " << vertex << endl;
                    used[vertex] = 1;
                    result.push_back(vertex);
                    visit_node[vertex] = 1;
                    count_art++;
                }
            }
            low[vertex] = min(low[vertex], dfs[aux]);
        }
    }
 }


 void DFS(int v){
    visited[v] = 1;
    num_elements++;
    for(int i=0; i < nnodes; i++){
        int aux = graph[v][i];
        if( aux == 1   ){
                if(visit_node[i]==1){
                    if(!visited[i]){
                        DFS(i);
                    }
                }

        }

    }

 }



int main()
{
    int value;
     d_time=0;
 count_art=0;
 num_elements=0;
    scanf("%d", &nnodes);

    for(int k=0; k< nnodes; k++){
        low[k] = 0;
        used[k] = 0;
                dfs[k] = -1;
                        parent[k] = -1;
visit_node[k]=0;



    }

    for(int i=0;i<nnodes; i++){
        for(int j=0;j<nnodes;j++){
            scanf("%d",&value);
            graph[i][j] = value;
        }
    }
    /*for(int i=0;i<nnodes; i++){
        if(dfs[i] == -1)
        {
        ART(i);
        }
    }*/

    ART(4);
    DFS(result[0]);
    cout << "dfs \n";
    for(int i =0; i<nnodes; i ++){
      cout << dfs[i] << " ";
    }
    cout << endl;

    cout << "low \n";
    for(int i =0; i<nnodes; i ++){
      cout << low[i] << " ";
    }
    cout << endl;
    if(count_art>1 && num_elements == (int)result.size() ){
        cout << "True" << endl;
    }
    else{
        cout << "False" << endl;
    }
    return 0;
}
