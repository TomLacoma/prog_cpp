#pragma once
#include <iostream>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>

using namespace std;


class Tableau{

  public:
  Tableau();
  ~Tableau();
  Tableau(int);
  Tableau(const Tableau&);
  Tableau(string);

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
  Matrix(int);
  Matrix(const Matrix&);

  void produit(Matrix&, Matrix&);
  void prod_ligne(Matrix&, Matrix&, int);

  int send(int, int, int); //Envoie la matrice M[i,j[ sur le réseau (ou la formate)
  void receive();

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

  void fill(double data, int n, int m);

  void fill_id();
  void zero_out();
  void randomize();
  void lFlip(int, int);
  void cFlip(int, int);

  void* toPtr();

  int send_line(int, int);
  int send_block(int, int, int);
  int recv_line(int, int);

  Tableau line(int);
  Matrix lines(int, int);
  string lineToStr(int);
  Tableau column(int);
};

Matrix operator * (double, Matrix&);
