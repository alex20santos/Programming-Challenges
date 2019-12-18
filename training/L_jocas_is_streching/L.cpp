#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <math.h>
using namespace std;

#define INF 9999999;

struct node
{
    int x,y;
};

struct edge
{
    int s,d;
    double c;
};

vector<node> coord;
int nnodes;
double graph[750][750];
vector<edge> edges;
int nC = 0;


double dEuclidean(int x1,int y1,int x2,int y2){
    return sqrt(fabs(x1-x2) * fabs(x1-x2) + fabs(y1-y2) * fabs(y1-y2));
}

void reset(){
    coord.clear();
    edges.clear();

}

bool comp(const edge &a,const edge &b){
    return a.c > b.c;
}


// A structure to represent a subset for union-find
struct subset
{
    int parent;
    int rank;
};

// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Attach smaller rank tree under root of high
    // rank tree (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    // If ranks are same, then make one as root and
    // increment its rank by one
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}


// The main function to construct MST using Kruskal's algorithm
void KruskalMST()
{
    double sum = 0;
    int V = nnodes;
    int e = 0;  // An index variable, used for result[]

    // Step 1:  Sort all the edges in non-decreasing
    // order of their weight. If we are not allowed to
    // change the given graph, we can create a copy of
    // array of edges
    sort(edges.begin(),edges.end(),comp);

    // Allocate memory for creating V ssubsets
    struct subset *subsets = (struct subset*) malloc( V * sizeof(struct subset) );

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is equal to V-1
    while (!edges.empty())
    {
        // Step 2: Pick the smallest edge. And increment
        // the index for next iteration
        struct edge next_edge = edges.back();

        int x = find(subsets, next_edge.s);
        int y = find(subsets, next_edge.d);

        // If including this edge does't cause cycle,
        // include it in result and increment the index
        // of result for next edge
        if (x != y)
        {
            Union(subsets, x, y);
            sum += next_edge.c;
        }

        edges.pop_back();
        // Else discard the next_edge
    }

    printf("%.2lf\n",sum);


    return;
}

int main(){
    int x,y;
    int s,d;
    double e;

    while(scanf("%d",&nnodes) != EOF){

        for (int i = 0; i < nnodes; i++){
            node Node;
            scanf("%d %d",&x,&y);

            Node.x = x;
            Node.y = y;

            coord.push_back(Node);

        }

        for (int i = 0; i < nnodes; i++)
        {
            for (int j = 0; j < nnodes; j++){
                 graph[i][j] = -1;
            }
        }


        for (int i = 0; i < nnodes; i++){
            for (int j = i+1; j < nnodes; j++){
                e = dEuclidean(coord[i].x,coord[i].y,coord[j].x,coord[j].y);
                graph[i][j] = e;
            }
        }

        scanf("%d",&nC);

        for (int i = 0; i < nC; i++){
            scanf("%d %d",&s,&d);
            s--;
            d--;
            if(s > d){
                graph[d][s] = 0;
            }
            else{
                graph[s][d] = 0;
            }
        }

        for(int i = 0; i < nnodes;i++ ){
            for (int j = 0; j < nnodes; j++)
            {
                if(graph[i][j] != -1){
                    edge Edge;
                    Edge.s = i;
                    Edge.d = j;
                    Edge.c =  graph[i][j];
                    edges.push_back(Edge);
                }

            }

        }

        /*for (int i = 0; i < edges.size(); i++)
        {
            cout << "s: " << edges[i].s << "d: " << edges[i].d << "c :" << edges[i].c << "\n";
        }*/

        /*cout << "\n";*/


        KruskalMST();

        reset();

    }



    return 0;
}
