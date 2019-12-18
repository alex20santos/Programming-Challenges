#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

bool bus1[50][50];
bool bus2[50][50];
int b1, b2;

void reset(int a){
    
    for (int i = 0; i < a; i++){
        for (int j = 0; j < a; j++){
            bus1[i][j] = false;
            bus2[i][j] = false;
        }
    }
}

void fwbus1(int V){
    for (int k = 0; k < V; k++){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V;j++){
                if(bus1[i][k] && bus1[k][j])
                    bus1[i][j] = true;
            }
        }
    }
}

void fwbus2(int V){
    for (int k = 0; k < V; k++){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V;j++){
                if(bus2[i][k] && bus2[k][j])
                    bus2[i][j] = true;
            }
        }
    }
}

bool comp(int V){
    
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++){
            if(bus1[i][j] != bus2[i][j])
                return false;
        }
    }
    return true;
    
}

int main(){
    
    int ntestcases, c1, c2;
    char a1 , a2;

    int V1 = 0;
    int V2 = 0;

    int a;

    scanf("%u",&ntestcases);

    for(int i = 0; i < ntestcases; i++){
        if(i > 0) cout << "\n";
        
        scanf("%d",&b1);
        for (int j = 0; j < b1; j++){
            scanf(" %c %c",&a1,&a2);
            c1 = a1 - 65;
            c2 = a2 - 65;
            bus1[c1][c2] = true;
            if(c1 > V1)
                V1 = c1;
            if(c2 > V1)
                V1 = c2;
        }
        scanf("%d",&b2);
        for (int j = 0; j < b2; j++){
            scanf(" %c %c",&a1,&a2);
            c1 = a1 - 65;
            c2 = a2 - 65;
            bus2[c1][c2] = true;
            if(c1 > V2)
                V2 = c1;
            if(c2 > V2)
                V2 = c2;
        }

        if(V1 >= V2)
            a = V1;
        else
            a = V2;


        fwbus1(a+1);
        fwbus2(a+1);
        if(comp(a+1)) cout << "YES\n";
        else cout << "NO\n";
        if(i + 1 < ntestcases){
            reset(a+1);
            V1 = 0;
            V2 = 0;
        } 
    }
    return 0;
}