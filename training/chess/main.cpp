#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include<set>
using namespace std;
#define DEBUGe


typedef struct Point{
    int x,y;
}Point;

inline bool operator(const Point &lhs, const Point &rhs)
{
  if(lhs.x == rhs.x)
    return lhs.y < rhs.y;
  return lhs.x < rhs.x;
}

set<Point> points_set;


vector<Point> calculate_next_points(Point point){
  vector<Point> v;
  Point new_p;
  int vx[] = {-2,2,1,-1};
  int vy[] = {-1,1,2,-2};
  for(int i=0;i<2;i++){
    for(int j=0;j<2;j++){
      new_p.x = point.x + vx[i];
      new_p.y = point.y + vy[j];
      v.push_back(new_p);
    }
  }
  for(int i=2;i<4;i++){
    for(int j=2;j<4;j++){
      new_p.x = point.x + vx[i];
      new_p.y = point.y + vy[j];
      v.push_back(new_p);
    }
  }
  return v;
}


void expand(Point p, int num_plays){
  vector<Point> next_points;
  bool is_in = false;
  if(num_plays == 0 ){
    is_in = points_set.find(p) != points_set.end();
    if(is_in == false){
      points_set.insert(p);
    }
    return;
  }
  else{
    num_plays--;
    is_in = points_set.find(p) != points_set.end();
    if(is_in == false){
      points_set.insert(p);
    }
    next_points = calculate_next_points(p);
    for(int i=0;i<(int)next_points.size();i++){
      expand(next_points[i],num_plays);
    }
    return;
  }
}


void input(){
    int k,x,y,plays;
    Point p;
    while(scanf("%d",&k) != EOF){
      for(int a=0; a<k;a++){
        scanf("%d",&x);
        p.x = x;
        scanf("%d",&y);
        p.y = y;
        scanf("%d",&plays);
        expand(p,plays);
      }
    }
    cout << (int)points_set.size() << endl;
}

int main() {
  clock_t begin = clock();
  input();
  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "time:"<<elapsed_secs <<endl;
  return 0;
}
