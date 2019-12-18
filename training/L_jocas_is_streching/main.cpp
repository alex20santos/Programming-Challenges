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


struct Edge{
    int src, dest;
		double weight;
};


struct Subset{
    int parent;
    int rank;
};

vector<Edge> edges;
vector<pair<int,int> > points;
int num_nodes;
vector<Subset> subsets(750);

bool compare(const Edge &e1, const Edge &e2){
	return e1.weight > e2.weight;
}


// A utility function to find set of an element i
// (uses path compression technique)
int find(struct Subset subsets[], int i)
{
    // find root and make root as parent of i
    // (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct Subset subsets[], int x, int y)
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
    int V = num_nodes;
    vector<Edge> result;
    // Step 1:  Sort all the edges in non-decreasing
    // order of their weight. If we are not allowed to
    // change the given graph, we can create a copy of
    // array of edges
    sort(edges.begin(),edges.end(),compare);

    // Allocate memory for creating V ssubsets
    struct Subset *subsets = (struct Subset*) malloc( V * sizeof(struct Subset) );

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
        struct Edge next_edge = edges.back();

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does't cause cycle,
        // include it in result and increment the index
        // of result for next edge
        if (x != y)
        {
            Union(subsets, x, y);
            sum += next_edge.weight;
            result.push_back(next_edge);
        }

        edges.pop_back();
        // Else discard the next_edge
    }

    printf("%.2lf\n",sum);
    for(int i=0;i<(int)result.size();i++){
      printf("%d -- %d == %lf\n", result[i].src, result[i].dest, result[i].weight);
    }

    return;
}

int main(){
	int n_edges;
	while(scanf("%d",&num_nodes) != EOF){
		scanf("%d",&n_edges);
		for(int j=0;j<n_edges; j++){
			Edge e;
			scanf("%d %d %lf" ,&e.src, &e.dest, &e.weight);
			e.src = e.src -1;
			e.dest = e.dest -1;

			//e.weight = (double) sqrt(fabs(points[e.src].first - points[e.dest].first) * fabs(points[e.src].first - points[e.dest].first)
			//	  + fabs(points[e.src].second - points[e.dest].second) * fabs(points[e.src].second - points[e.dest].second));
			edges.push_back(e);
		}
		sort(edges.begin(),edges.end(),compare);
		for(int i=0;i<(int)edges.size();i++){
			cout << edges[i].src << " " << edges[i].dest <<" "<<  edges[i].weight << endl;;
		}
		cout << endl;
		KruskalMST();
		/*for(int i=0;i<(int)edges.size();i++){
			cout << edges[i].src << " " << edges[i].dest <<" "<<  edges[i].weight << endl;;
		}
		cout << endl;*/
		edges.clear();
		points.clear();
		subsets.clear();
	}


  return 0;
}
