#pragma once
#include <iostream>
#include "tableau.h"

class MatrixBlock{ //Pour cauculer les lignes [start_line, stop_line[ de c=a*b en parallèle
public:
  Matrix* _a;
  Matrix* _b;
  Matrix* _c;
  int _start_line;
  int _stop_line;

  MatrixBlock();
  MatrixBlock(Matrix*, Matrix*, Matrix*, int, int);
};

void* start_routine(void*);
