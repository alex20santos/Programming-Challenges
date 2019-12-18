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
#define N 26

int n1,n2;
int graph1[N][N];
int graph2[N][N];
int C1[N][N];
int C2[N][N];


void floyd_warshall(){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(graph1[i][j] == 1){
        C1[i][j] = true;
      }
    }
  }
  for(int k = 0; k < N; k++){
    for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){
        if(C1[i][k] && C1[k][j]){
          C1[i][j] = true;
        }
      }
    }
  }
}

void floyd_warshall2(){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(graph2[i][j] == 1){
        C2[i][j] = true;
      }
    }
  }
  for(int k = 0; k < N; k++){
    for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){
        if(C2[i][k] && C2[k][j]){
          C2[i][j] = true;
        }
      }
    }
  }
}

bool compare_graphs(){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      if(C1[i][j]){
        if(!C2[i][j]){
          return false;
        }
      }
      if(C2[i][j]){
        if(!C1[i][j]){
          return false;
        }
      }
    }
  }
  return true;
}

void reset(){
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      graph1[i][j] = 0;
      graph2[i][j] = 0;
      C1[i][j] = false;
      C2[i][j] = false;
    }
  }
}


int main(){
  int ncases;
  char city1, city2;
  scanf("%d",&ncases);
  for(int k = 0; k < ncases; k++){
    if(k > 0)
      printf("\n");
    scanf("%d",&n1);
    for(int i = 0; i < n1; i++){
      scanf(" %c %c",&city1,&city2);
      int p1, p2;
      p1 = city1 - 65;
      p2 = city2 - 65;
      graph1[p1][p2] = 1;
    }
    scanf("%d",&n2);
    for(int i = 0; i < n2; i++){
      scanf(" %c %c",&city1,&city2);
      int p1, p2;
      p1 = city1 - 65; // 'Z' é 90
      p2 = city2 - 65;
      graph2[p1][p2] = 1;
    }
    floyd_warshall();
    floyd_warshall2();

    if(compare_graphs())
      printf("YES\n");
    else{
      printf("NO\n");
    }
    reset();
  }
  return 0;
}
