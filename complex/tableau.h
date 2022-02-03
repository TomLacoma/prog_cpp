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

  void write(double, int);

  void operator = (const Tableau&);
  double operator [] (int);

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
  Matrix operator * (double);
  double* operator [] (int);

  void operator += (Matrix&);
  void operator -= (Matrix&);
  void operator *= (Matrix&);
  void operator *= (double);

  void operator = (const Matrix&);

  void write(double data, int n, int m);

  void fill_id();
  void zero_out();
  void randomize();
  void lFlip(int, int);
  void cFlip(int, int);

  Tableau line(int);
  Tableau column(int);
};

Matrix operator * (double, Matrix&);
