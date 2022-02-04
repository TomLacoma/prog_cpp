#include <iostream>
#include "complex.h"
#include "tableau.h"
#include <string>
#include <chrono>
#include <cassert>

#define MAX_SIZE 200

using namespace std;
using namespace std::chrono;

int main(){

  Matrix A(2,3);
  Matrix B(5,6);

  Matrix C = A*B;

  return 0;
}
