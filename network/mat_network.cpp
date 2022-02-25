#include "mat_network.h"


Matrix recv_block(int f){
	int m,n,i,j;

	int r = read(f, &n, sizeof(n)); //n lignes
	r = read(f, &m, sizeof(m)); // n col
	r = read(f, &i, sizeof(i)); // indice ligne début
	r = read(f, &j, sizeof(j)); //indice ligne fin
  assert(r!=-1);

  Matrix A(n,m);

  for(int _i=i; _i<j; _i++){
    A.recv_line(f, _i);
    //std::cout << "_Received line "<< _i << '\n';
  }
	return A;
}

int Matrix::send_block(int s, int i, int j){
  int r = write(s, &_n, sizeof(_n));
  r = write(s, &_m, sizeof(_m));
  r = write(s, &i, sizeof(i)); //début de ligne à envoyer
  r = write(s, &j, sizeof(j)); //fin ligne à envoyer, exclue

  for(int k=i; k<j; k++){
    this->send_line(s, k);
  }
  return r == sizeof(_n);
}
