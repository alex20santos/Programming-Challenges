#include<iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#define NODEBUG
#define VALIDATION // Usar VALIDATION para dar print dos eventos escolhidos
using namespace std;


struct Event {
   int deadline,duration,profit;
};

struct less_than_key{
    inline bool operator() (Event e1, Event e2){
        return (e1.deadline < e2.deadline);
    }
};


vector<Event> events;
int num_events;
int max_deadline=0;
vector<vector<int> >  matrix;


vector<vector<int> > init_matrix(int n, int d){
  vector<vector<int> > m(n, vector<int>(d,-1));
  return m;
}


void print_matrix(){
  for(int i=0; i<matrix.size();i++){
    for(int j =0;j<matrix[i].size();j++){
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;

}

void maximize_profit(){
  for(int l=0;l<=max_deadline;l++){
    matrix[0][l] = 0;
  }
  cout << "iniit" << endl;
  print_matrix();

  for(int i=1; i <= num_events;i++){
    for(int j=0;j <= max_deadline;j++){
      int t = min(j,events[i-1].deadline) - events[i-1].duration; // último tempo em que poderá ser possível colocar o envento
                                                                  //  e os restantes eventos terminam no tempo t
      if(t < 0){ // não é possível
        matrix[i][j] = matrix[i-1][j];
      }
      else{
        /* caso seja possível agendar temos duas possibilidades:
            -> não colocar e ficamos com o melhor profit no tempo em que está
            -> colocar o valor da soma do profit do evento atual com o profit que temos até ao momento em que é possível
          agendar o evento (todos os outros eventos terminam até ao tempo t)
        */
        matrix[i][j] = max(matrix[i-1][j], events[i-1].profit + matrix[i-1][t]);
      }
      print_matrix();
    }
  }
}

void validation(int i, int t){
  if(i == 0){
    return;
  }
  if(matrix[i][t] == matrix[i-1][t]){
    validation(i-1,t);
  }
  else{
    int l = min(t,events[i-1].deadline) - events[i-1].duration;
    validation(i-1,l);
    cout << "index:" << i-1 << " start_time:" << l << " end_time:"<<l+events[i-1].duration
    << " deadline:"<<events[i-1].deadline << " profit:" << events[i-1].profit  << endl;
  }
}


int main() {

  int n_events,a,deadline,duration,profit;

  scanf("%d",&n_events);
  num_events = n_events;
  for(a=0; a<n_events;a++){
    Event event;
    scanf("%d",&deadline);
    scanf("%d",&duration);
    scanf("%d",&profit);
    event.profit = profit;
    event.duration = duration;
    event.deadline = deadline;
    if(deadline>max_deadline){
      max_deadline = deadline;
    }
    events.push_back(event);
  }
  sort(events.begin(),events.end(),less_than_key()); // ordena por maior deadline
  matrix = init_matrix(n_events+1,max_deadline+1); //inicializa matriz com numero de enventos (+1)

  maximize_profit();

  cout << matrix[num_events][max_deadline] << endl;
  #ifdef VALIDATION
  cout << n_events << " " << max_deadline << endl;
  validation(n_events, max_deadline );
  #endif
  return 0;
}
