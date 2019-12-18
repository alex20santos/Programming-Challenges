#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <list>


using namespace std;

int funtions[50][50];
int nfuntions;

bool BFS(int s){

    int vertex = s;

    bool *visited = new bool[nfuntions];

    for(int i = 0; i < nfuntions; i++)
        visited[i] = false;

    list<int> queue;

    visited[s] = true;
    queue.push_back(s);

    while (!queue.empty())
    {
        s  = queue.front();
        queue.pop_front();

        for (int i = 1; i <= funtions[s][0] ; i++){
            int aux = funtions[s][i];
            if(aux == vertex){
                return true;
            }

            if(!visited[aux]){
                visited[aux] = true;
                queue.push_back(aux);
            }
        }
    }

    return false;


}

int main(){
    int ncalls;
    vector<int> recursive;

    scanf("%u",&nfuntions);

    for (int i = 0; i < nfuntions; i++)
    {
        scanf("%u",&ncalls);
        funtions[i][0] = ncalls;
        for (int j = 1; j <= ncalls; j++){
            scanf("%u", &funtions[i][j]);
        }
    }
    for(int i=0;i<nfuntions; i++){
      for (int j = 1; j <= funtions[i][0] ; j++){
        cout << funtions[i][j] << " ";
      }
      cout << endl;
    }

    for (int i = 0; i < nfuntions; i++){
        if(BFS(i)){
            cout << i << "\n";
        }
    }

    return 0;
}
