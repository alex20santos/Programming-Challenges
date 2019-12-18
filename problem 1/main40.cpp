#include<iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

struct Source {
   vector<int> targets; // para cada source guarda um target e para cada target guarda um source
};

struct LRPoint {
   int x,y;
};

struct Line{
   int p1,p2;
};


LRPoint room_points[81]; // todos os pontos(coordenadas da sala)
Source sources[81];
Line lines[28]; // max linhas (colliders) possivel
int min_intersections=10000;
int intersections[81][81][81][81]; // intersecções e não intersecções guardadas
int max_devices;
int total_points;
bool room_points_visited[81]; //se ponto está ou não marcado como visitado
int  used_devices[81]; // guarda device no indice do ponto
vector<Line> final_result;


int orientation(int p, int q, int r) {
    int val = (room_points[q].y - room_points[p].y) * (room_points[r].x - room_points[q].x) -
              (room_points[q].x - room_points[p].x) * (room_points[r].y - room_points[q].y);
    if (val == 0) return 0;

    return (val > 0)? 1: 2;
}

bool onSegment(int p, int q, int r){
    if (room_points[q].x <= max(room_points[p].x, room_points[r].x) && room_points[q].x >= min(room_points[p].x, room_points[r].x) &&
        room_points[q].y <= max(room_points[p].y, room_points[r].y) && room_points[q].y >= min(room_points[p].y, room_points[r].y))
       return true;
    return false;
}

bool doIntersect(Line l1, Line l2) {
    /* implementação baseada nos slides de computação geometrica e no site geeksforgeeks.com*/

    /* endpoints coincidentes */
    if(l1.p1 == l2.p1 || l1.p2 == l2.p2 || l1.p2 == l2.p1 || l1.p1 == l2.p2)
      return false;

    int o1 = orientation(l1.p1, l1.p2, l2.p1);
    int o2 = orientation(l1.p1, l1.p2, l2.p2);
    int o3 = orientation(l2.p1, l2.p2, l1.p1);
    int o4 = orientation(l2.p1, l2.p2, l1.p2);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(l1.p1, l2.p1, l1.p2))
      return true;

    if (o2 == 0 && onSegment(l1.p1, l2.p2, l1.p2))
      return true;

    if (o3 == 0 && onSegment(l2.p1, l1.p1, l2.p2))
      return true;

    if (o4 == 0 && onSegment(l2.p1, l1.p2, l2.p2))
      return true;

    return false;
}


int calculate_intersections(Line line,int num_lines,int actual_intersections){
  int count=0;
  for(int i=0;i < num_lines;i++){

    int res = intersections[line.p1][line.p2][lines[i].p1][lines[i].p2] ;
    /* 0->não calculado 1->intersectado 2->não intersectado */

    if(res == 2){
      continue;
    }
    else if(res == 1){
      actual_intersections++;
      count++;
      if(actual_intersections >= min_intersections){
        return count;
      }
    }
    else if(doIntersect(line,lines[i])){
      //guarda como intersecção
      intersections[line.p1][line.p2][lines[i].p1][lines[i].p2] = 1;
      intersections[line.p2][line.p1][lines[i].p1][lines[i].p2] = 1;
      intersections[line.p1][line.p2][lines[i].p2][lines[i].p1] = 1;
      intersections[line.p2][line.p1][lines[i].p2][lines[i].p1] = 1;
      count++;
      actual_intersections++;
      if(actual_intersections >= min_intersections){
        return count;
      }
    }
    else{
      //guarda como não intersecção
      intersections[line.p1][line.p2][lines[i].p1][lines[i].p2] = 2;
      intersections[line.p2][line.p1][lines[i].p1][lines[i].p2] = 2;
      intersections[line.p1][line.p2][lines[i].p2][lines[i].p1] = 2;
      intersections[line.p2][line.p1][lines[i].p2][lines[i].p1] = 2;
    }
  }
  return count;
}


void func(int actual_device, int actual_lines, int actual_intersections){
  bool to_leave = false;
  Line new_line;
  int count,i,j,newLineNumber;

  if(min_intersections == 0){
    return;
  }

  if(actual_intersections >= min_intersections){
    return;
  }

  if(actual_device == max_devices){
    if(actual_intersections < min_intersections){
      min_intersections = actual_intersections;
    }
    return;
  }

  for(i=0;i<total_points;i++){
      if(room_points_visited[i]==false){
        room_points_visited[i]=true; //marca ponto como visitado
        used_devices[actual_device] = i; // associa device ao ponto i
        cout << "device "<< actual_device << " on " << i << " point " << endl;

        newLineNumber = actual_lines;
        count = actual_intersections;
        new_line.p1 = i; //inicio do segmento
        for(j=0;j<(int)sources[actual_device].targets.size();j++){
          if(used_devices[sources[actual_device].targets[j]] > -1){ // se o device estiver associado a um ponto
            new_line.p2 = used_devices[sources[actual_device].targets[j]]; // fim do segmento
            if(actual_device > 2) // cortar quando não há pelo menos 3 pontos (não há intersecções)
              count += calculate_intersections(new_line,actual_lines,count);
            if(count >= min_intersections){
              to_leave = true;
              break;
            }
            lines[newLineNumber] = new_line; //adiciona nova linha criada ao array
            newLineNumber++; // contador para poder adicionar novas linhas (colliders)
          }
        }
        if(!to_leave){
          func(actual_device+1, newLineNumber,count);
        }

        room_points_visited[i] = false; // backtracking
        used_devices[actual_device] = -1;
        to_leave = false;
      }
    }
}


int main() {
  int x,y,col,s,t,j,i,a;
  LRPoint lr_p;

  scanf("%d",&total_points);
  for(a=0; a<total_points;a++){
    scanf("%d",&x);
    lr_p.x = x;
    scanf("%d",&y);
    lr_p.y = y;
    room_points[a] = lr_p;
    used_devices[a]=-1;
    room_points_visited[a]=false;
  }
  scanf("%d",&max_devices);
  scanf("%d",&col);
  memset(intersections,0,81*81*81*81*sizeof(int));

  for(j=0;j<col;j++){
    scanf("%d",&s);
    scanf("%d",&t);
    sources[s-1].targets.push_back(t-1);
    sources[t-1].targets.push_back(s-1);
  }

  for (i = 0; i < total_points; i++) {
    room_points_visited[i] = true;
    used_devices[0] = i; // device 0 está no ponto i
    cout << "device 0 on " << i << " point " << endl;
    func(1,0,0);
    cout << "end recursion " << endl;
    room_points_visited[i] = false;
    used_devices[0] = -1;
    cout << endl;
  }

  cout << min_intersections<< endl;
  return 0;
}
