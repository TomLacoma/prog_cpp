#include "tableau.h"
#include <cstring>
#include <cassert>
#include <pthread.h>

using namespace std;

Tableau::Tableau(int n){
  _len = n;
  _data = new int [n];

  for(int i=0; i<n;i++){
    _data[i] = 0;
  }
}


Tableau::~Tableau(){
  //cout << "Rickrolled " << _data << endl;
  delete [] _data;
  //cout << "Freed " << _data << endl;
}

Tableau::Tableau(const Tableau &aux){ //Constructeur de recopie, important pour la duplication propre des objets (pointeurs)
  _len = aux._len;
  _data = new int[_len];
  memcpy(_data ,aux._data, _len*sizeof(int));
}


void Tableau::operator = (const Tableau &aux){ //Surcharge de l'opérateur = (assignation), ici, t2=t1 <=> t2.operator=(t1)
  if(this!=&aux){
    if(&_data!=NULL){
      delete[] _data;
    }
    _len = aux._len;
    _data = new int[_len];
    memcpy( _data, aux._data, _len*sizeof(int));
  }
}

void Tableau::write(double data, int index){
  _data[index] = data;
}

double Tableau::operator [] (int index){
  assert(index>=0 && index<_len);
  return _data[index];
}

std::ostream &operator << (std::ostream &s, Tableau &t){ //Surcharge du << pour tableaux
  for(int i=0; i<t._len; i++){
    s << t._data[i] << " ";
  }
  s << endl;
  return s;
}


void dump(Tableau t){ //equivalent du cout << Tableau mais en externe à la fonction ==> copie l'objet dans la pile (peut générer des erreurs de double destruction d'un objet)
  for(int i=0; i<t._len; i++){
    cout << t._data[i] << " " << i << " ";
  }
  cout << endl;
}


//Matrix
Matrix::Matrix(int n, int m){//création d'une matrice à n lignes et m colonnes
  _n = n;
  _m = m;
  _data = new double* [n];
  for(int i=0; i<_n; i++){
    _data[i] = new double [m];
    for(int j=0; j<_m; j++){
      _data[i][j] = 0;
    }
  }
  //cout << "Created matrix " << n << "*" << m << " with address " << &_data << endl;
}

Matrix::Matrix(int n){//création d'une matrice à n lignes et m colonnes
  _n = n;
  _m = n;
  _data = new double* [n];
  for(int i=0; i<_n; i++){
    _data[i] = new double [n];
    for(int j=0; j<_m; j++){
      _data[i][j] = 0;
    }
  }
  //cout << "Created matrix " << n << "*" << m << " with address " << &_data << endl;
}

Matrix::~Matrix(){
  delete[] _data;
  //cout << "Freed " << &_data << endl;
}

int Matrix::send_line (int s, int l) {
    ssize_t size = _n * sizeof(double);
    return size == write(s, _data[l], size);
}

int Matrix::recv_line (int s, int l) {
    ssize_t size = _n * sizeof(double);
    return size == read(s, _data[l], size);
}

Matrix::Matrix(const Matrix &aux){
  _n = aux._n;
  _m = aux._m;
  _data = new double* [_n];
  for(int i=0; i<_n; i++){
    _data[i] = new double [_m];
  }
  memcpy(_data, aux._data, _n*_m*sizeof(double));
}

void Matrix::fill_id(){
  for(int i=0; i<_n; i++){
    for(int j=0; j<_m; j++){
      if(i==j){
        _data[i][j] = 1;
      }
      else{
        _data[i][j] = 0;
      }
    }
  }
}

void Matrix::zero_out(){
  for(int i=0; i<_n; i++){
    for(int j=0; j<_m; j++){
      _data[i][j] = 0;
      }
    }
  }


std::ostream &operator << (std::ostream &s, Matrix &mat){ //Surcharge du << pour matrices
  for(int i=0; i<mat._n; i++){
    for(int j=0; j<mat._m; j++){
        s << mat._data[i][j] << " ";
    }
    s << endl;
  }
  return s;
}

double* Matrix::operator[] (int n){
  return _data[n];
}

void Matrix::operator = (const Matrix &mat){
  if(this!=&mat){
    if(_data!=NULL){
      delete[] _data;
      //cout << "Overwrite" << endl;
    }
    _n = mat._n;
    _m = mat._m;
    _data = new double* [_n];
    for(int i=0; i<_n; i++){
      _data[i] = new double [_m];
    }
    memcpy(_data, mat._data, _n*_m*sizeof(double));
  }
}

Matrix Matrix::operator + (Matrix &mat){
  Matrix tmpMat(_n,_m);
  for(int i=0; i<mat._n; i++){
    for(int j=0; j<mat._m; j++){
        tmpMat[i][j] = _data[i][j] + mat._data[i][j];
        //cout << mat._data[i][j] << " " << i << " " << j << endl;
    }
  }
  return tmpMat;
}

Matrix Matrix::operator - (Matrix &mat){
  Matrix tmpMat(_n,_m);
  for(int i=0; i<mat._n; i++){
    for(int j=0; j<mat._m; j++){
        tmpMat[i][j] = _data[i][j] - mat._data[i][j];
        //cout << mat._data[i][j] << " " << i << " " << j << endl;
    }
  }
  return tmpMat;
}

Matrix Matrix::operator * (double scal){
  Matrix tmpMat(_n,_m);
  for(int i=0; i<_n; i++){
    for(int j=0; j<_m; j++){
        tmpMat[i][j] = _data[i][j] * scal;
        //cout << mat._data[i][j] << " " << i << " " << j << endl;
    }
  }
  return tmpMat;
}

Matrix Matrix::operator * (Matrix &mat){
  assert(_m==mat._n);
  Matrix tmpMat(_n,mat._m);
  for(int i=0; i<_n; i++){
    for(int j=0; j<mat._m; j++){
        for(int k=0; k<_m; k++){
          tmpMat[i][j] += _data[i][k]*mat._data[k][j];
        }
    }

  }

  return tmpMat;
}

Matrix operator * (double scal, Matrix &mat){

  Matrix tmpMat(mat._n,mat._m);
  for(int i=0; i<mat._n; i++){
    for(int j=0; j<mat._m; j++){
        tmpMat[i][j] = mat._data[i][j] * scal;
        //cout << mat._data[i][j] << " " << i << " " << j << endl;
    }
  }
  return tmpMat;
}

void Matrix::randomize(){
  for(int i=0; i<_n;i++){
    for(int j=0; j<_m;j++){
      _data[i][j] = random()%10;
    }
  }
}

void Matrix::fill(double data, int n, int m){
    assert(n<_n);
    assert(n>=0);
    assert(m<_m);
    assert(m>=0);
    _data[n][m] = data;
}

void Matrix::operator += (Matrix &mat){
  *this = *this + mat;
}

void Matrix::operator -= (Matrix &mat){
  *this = *this - mat;
}

void Matrix::operator *= (Matrix &mat){
  *this = *this * mat;
}

void Matrix::operator *= (double l){
  *this = *this * l;
}

void Matrix::cFlip(int c1, int c2){//flips columns c1 and c2
  double tmp;
  for(int i=0; i<_n; i++){
    tmp = _data[i][c1];
    this->fill(_data[i][c2], i, c1);
    this->fill(tmp, i, c2);
  }
}

void Matrix::lFlip(int l1, int l2){ //flips lines l1 and l2
  double tmp;
  for(int j=0; j<_m; j++){
    tmp = _data[l1][j];
    this->fill(_data[l2][j], l1, j);
    this->fill(tmp, l2, j);
  }
}

Tableau Matrix::line(int l){
  Tableau tmpTab(_m);
  for(int i=0; i<_m; i++){
  tmpTab.write(_data[l][i], i);
  }
  return tmpTab;
}

std::string Matrix::lineToStr(int l){
  std::string chaine;
  for(int i=0; i<_m; i++){
   chaine+= std::to_string(_data[l][i]) + ",";
  }
  return chaine;
}

Tableau Matrix::column(int c){
  Tableau tmpTab(_n);
  for(int j=0; j<_n; j++){
  tmpTab.write(_data[j][c], j);
  }
  return tmpTab;
}

Matrix Matrix::lines(int i, int j){ //Renvoie la sous matrice des lignes [i,j[ de &this
  assert(j>i && i>=0 && j<=_n);
  Matrix tmpMat(j-i, _m);
  for(int _i=i; _i<j; _i++){
    for(int _j=0; _j<_m; _j++){
      tmpMat.fill(_data[_i][_j], _i-i, _j);
    }
  }
  return tmpMat;
}


void Matrix::prod_ligne(Matrix &A, Matrix &B, int i){ //Calcule la ligne i du produit des matrices A et B, et les écrit dans la matrice &this
  assert(A._m==B._n);
  for(int j=0; j<B._m; j++){
    for(int k=0; k<A._m; k++){
      _data[i][j] += A._data[i][k]*B._data[k][j];
    }
  }
}

void Matrix::produit(Matrix &A, Matrix &B){
  assert(A._m==B._n);
  for(int i=0; i<A._n; i++){
    for(int j=0; j<B._m; j++){
      for(int k=0; k<A._m; k++){
        _data[i][j] += A._data[i][k]*B._data[k][j];
      }
    }
  }
}

void* Matrix::toPtr(){
  return this;
}

int Matrix::send(int f, int i, int j){//Envoie les lignes [i,j[ de la matrice sur le socket f
  int ret = write(f, this->lines(i,j).toPtr(), sizeof(Matrix));
  return ret;
}
