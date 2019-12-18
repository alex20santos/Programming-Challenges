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

using namespace std;


int m_pairwise, n_sequences;

vector<vector<int> > graph;

vector<vector<int> > init_matrix(int m, int n){
	vector<vector<int> > matrix(m, vector<int>(n,0));
	return matrix;
}

bool isBipartiteUtil(int src, int colorArr[])
{
    colorArr[src] = 1;

    // Create a queue (FIFO) of vertex numbers a
    // nd enqueue source vertex for BFS traversal
    queue <int> q;
    q.push(src);

    // Run while there are vertices in queue (Similar to BFS)
    while (!q.empty())
    {
        // Dequeue a vertex from queue ( Refer http://goo.gl/35oz8 )
        int u = q.front();
        q.pop();

        // Return false if there is a self-loop
        if (graph[u][u] == 1)
        return false;

        // Find all non-colored adjacent vertices
        for (int v = 0; v < n_sequences; ++v)
        {
            // An edge from u to v exists and
            // destination v is not colored
            if (graph[u][v] && colorArr[v] == -1)
            {
                // Assign alternate color to this
                // adjacent v of u
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }

            // An edge from u to v exists and destination
            // v is colored with same color as u
            else if (graph[u][v] && colorArr[v] == colorArr[u])
                return false;
        }
    }

    // If we reach here, then all adjacent vertices can
    // be colored with alternate color
    return true;
}


// Returns true if G[][] is Bipartite, else false
bool isBipartite()
{
    // Create a color array to store colors assigned to all
    // veritces. Vertex/ number is used as index in this
    // array. The value '-1' of colorArr[i] is used to
    // ndicate that no color is assigned to vertex 'i'.
    // The value 1 is used to indicate first color is
    // assigned and value 0 indicates second color is
    // assigned.
    int colorArr[n_sequences];
    for (int i = 0; i < n_sequences; ++i)
        colorArr[i] = -1;

    // This code is to handle disconnected graoh
    for (int i = 0; i < n_sequences; i++){
			if (colorArr[i] == -1){
	        if (isBipartiteUtil(i, colorArr) == false){
						return false;
					}
			}
		}

    return true;
}

int main(){
	int from, to;
	while(scanf("%d %d",&n_sequences, &m_pairwise ) != EOF){
		if(n_sequences>0 && m_pairwise >0){
			graph = init_matrix(n_sequences,n_sequences);

			for(int i=0;i<m_pairwise;i++){
			 scanf("%d %d", &from, &to);
			 //cout << from << " " << to << endl;
			 graph[from-1][to-1] = 1;
			 graph[to-1][from-1] = 1;
			}

			/*for(int i=0;i<n_sequences;i++){
				for(int j=0; j< n_sequences; j++){
				 cout << graph[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;*/

			if(isBipartite()){
				cout<<"No"<<endl;
			}
			else
				cout<<"Yes"<<endl;
		 }
	}

	return 0;
}
