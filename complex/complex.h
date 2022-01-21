#pragma once
#include <iostream>

using namespace std;

class Complex{
  float _x, _y;

  public:
    Complex();
    Complex(float, float);

    float real();
    float imag();
    float module();

    friend std::ostream & operator << (std::ostream & s, Complex & z);
};
