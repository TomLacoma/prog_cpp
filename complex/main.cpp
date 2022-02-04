#include <iostream>
#include "complex.h"
#include "tableau.h"
#include <string>
#include <chrono>
#include <cassert>
#include <fstream>


using namespace std;
using namespace std::chrono;

int main(int argc, char** argv){
assert(argc==2);

int p = atoi(argv[1]);


Matrix mat(p);
mat.randomize();
Matrix mat2(p);
mat2.randomize();
Matrix mat3(p);

auto start = high_resolution_clock::now(); //beggining of execution
mat3 = mat*mat2;

auto stop = high_resolution_clock::now();
auto duration = (double) duration_cast<microseconds>(stop - start).count();

cout << duration << endl;

auto start2 = high_resolution_clock::now(); //beggining of execution

mat3.produit(mat, mat2);

auto stop2 = high_resolution_clock::now();
auto duration2 = (double) duration_cast<microseconds>(stop2 - start2).count();

cout << duration2 << endl;



  return 0;
}
