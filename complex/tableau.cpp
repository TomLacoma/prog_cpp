#include "tableau.h"
#include <cstring>

using namespace std;

Tableau::Tableau(int n){
  _len = n;
  _data = new int [n];

  for(int i=0; i<n;i++){
    _data[i] = random()%100;
  }

  cout << "Created object of size " << _len << " and adress " << _data << endl;

}

Tableau::~Tableau(){
  //cout << "Rickrolled " << _data << endl;
  delete [] _data;
  cout << "Freed " << _data << endl;
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



std::ostream &operator << (std::ostream &s, Tableau &t){ //Surcharge du << pour tableaux
  for(int i=0; i<t._len; i++){
    s << t._data[i] << " " << i << " ";
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
Matrix::Matrix(int n, int m){
  _n = n;
  _m = m;
  _data = new double* [n];
  for(int i=0; i<_n; i++){
    _data[i] = new double [m];
  }
  cout << "Created matrix " << n << "*" << m << " with address" << &_data << endl;
}

Matrix::~Matrix(){
  delete[] _data;
  cout << "Freed " << &_data << endl;
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

std::ostream &operator << (std::ostream &s, Matrix &mat){ //Surcharge du << pour tableaux
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
    }
  }
  return tmpMat;
}
