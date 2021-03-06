#include "complex.h"
#include <cmath>

using namespace std;

//Complex
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


std::ostream &operator << (std::ostream &s, Complex z){
        s << z._x << "+" << z._y << "i";
        return s;
}

Complex Complex::operator + (Complex z2){
  return Complex(_x+z2.real(), _y+z2.imag());
}

Complex Complex::operator - (Complex z2){
  return Complex(_x-z2.real(), _y-z2.imag());
}

Complex Complex::operator * (Complex z2){
  return Complex(pow(_x,2)-pow(z2.imag(),2), _y*z2.real() + _x*z2.imag());
}
