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
  int off = 0;
  Tableau res(THREADS); //Nombre de lignes à assigner par thread
  for(int a=0; a<THREADS; a++){
    if(a<SIZE%THREADS){
      off++;
    }
    res.write(a*bloc_size+off,a);
  }

  cout << res;

  pthread_t* threads = new pthread_t [THREADS];
  MatrixBlock* blocks = new MatrixBlock [THREADS];
  void *status;



  Matrix A(SIZE);
  Matrix B(SIZE);
  Matrix C(SIZE);

  A.randomize();
  B.randomize();

  for(int a=0; a<THREADS; a++){ //répartition du gros du nombre de threads
    blocks[a] = MatrixBlock(&A, &B, &C, a*bloc_size, (a+1)*bloc_size);
    pthread_create(&threads[a], NULL, start_routine, &blocks[a]);
    pthread_join(threads[a], &status);
  }


  //cout << C;


  return 0;
}
