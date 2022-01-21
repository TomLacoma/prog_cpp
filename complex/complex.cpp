#include "complex.h"
#include <cmath>

using namespace std;

Complex::Complex(){
  _x = 0;
  _y = 0;
}

Complex::Complex(float x, float y){
  _x = x;
  _y = y;
}

float Complex::real(){
  return _x;
}

float Complex::imag(){
  return _y;
}

float Complex::module(){
  return pow((pow(_x,2) + pow(_y,2)), 1/2);
}


std::ostream &operator << (std::ostream &s, Complex &z){
        s << z._x << "+" << z._y << "i";
        return s;
}
