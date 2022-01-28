#include <iostream>
#include "complex.h"
#include "tableau.h"
#include <string>

using namespace std;

int main(){
/*
  Complex z(1,1);
  Complex a(3,2);
*/
/*
  Tableau tab(5);
  cout << tab;
  dump(tab);
*/

  Matrix mat(3,3);
  mat.fill_id();
  Matrix mat2(3,3);
  mat.fill_id();
  cout << mat;
  
  Matrix mat3(3,3);
  mat3 = mat + mat2;
  cout << mat3;

  return 0;
}
