#pragma once
#include <iostream>

using namespace std;


class Tableau{

  public:
  Tableau();
  ~Tableau();
  Tableau(int);
  Tableau(const Tableau&);

  int _len;
  int* _data;

  friend std::ostream &operator << (std::ostream &s, Tableau &t);

  void operator = (const Tableau&);
};

void dump(Tableau);

class Matrix{

public:

  double** _data;
  int _n,_m;

  Matrix();
  ~Matrix();
  Matrix(int, int);
  Matrix(const Matrix&);

  friend std::ostream &operator << (std::ostream &s, Matrix &mat);

  Matrix operator + (Matrix&);
  Matrix operator - (Matrix&);
  Matrix operator * (Matrix&);
  double* operator [] (int);

  void operator = (const Matrix&);

  void fill_id();
};
