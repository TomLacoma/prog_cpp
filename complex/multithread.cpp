#include "tableau.h"
#include "multithread.h"
#include <cstring>
#include <cassert>
#include <pthread.h>


void* start_routine(void* obj){
  MatrixBlock* arg = (MatrixBlock*) obj;
  std::cout << "test* " << arg->_start_line << '\n';
  for(int i=arg->_start_line; i<arg->_stop_line; i++){
    for(int j=0; j<arg->_b->_m; j++){
      for(int k=0; k<arg->_a->_m; k++){
        arg->_c->_data[i][j] += arg->_a->_data[i][k]*arg->_b->_data[k][j];
      }
    }
  }
  return NULL;
}

MatrixBlock::MatrixBlock(Matrix* A, Matrix* B, Matrix* C, int i1, int i2){
  _a=A;
  _b=B;
  _c=C;
  _start_line=i1;
  _stop_line=i2;
}

MatrixBlock::MatrixBlock(){
  _a=NULL;
  _b=NULL;
  _c=NULL;
  _start_line=0;
  _stop_line=0;
}
