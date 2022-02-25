#include <iostream>
#include "complex.h"
#include "tableau.h"
#include "multithread.h"
#include <string>
#include <chrono>
#include <cassert>

#define THREADS 8

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv){

  Matrix A(10, 7);
  A.randomize();

  cout << A << endl;

  Matrix B(10, 7);
  B = A.lines(0,10);
  cout << B << endl << sizeof(Matrix) << endl;
  cout << B.toPtr() << endl << sizeof(B.toPtr()) << endl;



  return 0;
}
