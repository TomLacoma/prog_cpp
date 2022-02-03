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
  Tableau tab2(5);
  tab2 = tab;
  cout << tab << endl << tab2 << endl;
  dump(tab);
*/


  Matrix mat(3,3);
  mat.fill_id();
  cout<<mat<<endl;
  mat.cFlip(1,2);
  cout<<mat<<endl;
  mat*=2;
  cout << mat;
  Tableau tmp = mat.column(1);
  cout << tmp;
  return 0;
}
