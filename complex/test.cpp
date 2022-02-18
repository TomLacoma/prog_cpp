
#include <iostream>
#include "complex.h"
#include "tableau.h"
#include "multithread.h"
#include <string>
#include <chrono>
#include <cassert>

#define THREADS 4

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv){
  assert(argc==2);

  int SIZE = atoi(argv[1]);

  int bloc_size = SIZE/THREADS;
  int excess = SIZE%THREADS; //excès de lignes à multiplier, entre 0 et bloc_size
  std::cout << excess << '\n';
  Tableau init(THREADS+1); //indice initial de la ligne du thread i
  for(int a=0; a<init._len; a++){
    if(excess>0){
      excess--;
      init.write(1, a);
    }
  }


  int start_i = 0;
  int stop_i = bloc_size+init[0];

  std::cout << start_i<< " " << stop_i  << "\t init" << bloc_size << '\n';

  cout << init;

  pthread_t* threads = new pthread_t [THREADS];
  MatrixBlock* blocks = new MatrixBlock [THREADS];
  void *status;



  Matrix A(SIZE);
  Matrix B(SIZE);
  Matrix C(SIZE);

  A.randomize();
  B.randomize();

  for(int a=0; a<min(THREADS, SIZE); a++){ //répartition du gros du nombre de threads
    blocks[a] = MatrixBlock(&A, &B, &C, start_i, stop_i);
    std::cout << "pre " <<  start_i<< " " << stop_i  << "\t" << init[a]<< '\n';
    pthread_create(&threads[a], NULL, start_routine, &blocks[a]);
    pthread_join(threads[a], &status);

    start_i=stop_i;
    stop_i+=bloc_size+init[a+1];
}

  cout << C;


  return 0;
}
