#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <cstring>
#include "base.h"
#include <unistd.h>
#include <cassert>
#include "../matrix/multithread.h"
#include "../matrix/tableau.h"
#include "mat_network.h"

using namespace std;


void * hconnect (void * fd)

{
	std::cout << "Incoming connection" << '\n';
	int f = *((int *)fd);

	int m,n,i,j;

	int r = read(f, &n, sizeof(n)); //n lignes
	r = read(f, &m, sizeof(m)); // n col
	r = read(f, &i, sizeof(i)); // indice ligne début
	r = read(f, &j, sizeof(j)); //indice ligne fin
  assert(r!=-1);

	//std::cout << n << "\t" << m << "\t" << i << "\t" << j << "\t" << "\n";

  Matrix A(n,m);

  for(int _i=i; _i<j; _i++){
		//std::cout << "Receiving line "<< _i << " of A\n";
    A.recv_line(f, _i);
  }

	//std::cout << "coucou" << '\n';

	r = read(f, &n, sizeof(n)); //n lignes
	r = read(f, &m, sizeof(m)); // n col
	r = read(f, &i, sizeof(i)); // indice ligne début
	r = read(f, &j, sizeof(j)); //indice ligne fin
  assert(r!=-1);

  Matrix B(n,m);
	//std::cout << n << "\t" << m << "\t" << i << "\t" << j << "\t" << "\n";
  for(int _i=i; _i<j; _i++){
		//std::cout << "Receiving line "<< _i << "of B\n";
    B.recv_line(f, _i);
  }

	//std::cout << "coucouB" << '\n';

/*
	Matrix B;
	B = recv_block(f);//matrix B, full
	std::cout << "coucou2" << '\n';*/

	cout << "Received :" << endl << A << endl << B << endl;

	Matrix C(A._m, B._n);
	for(int p=i; p<j; p++){
    for(int q=0; q<A._m; q++){
      for(int k=0; k<A._m; k++){
        C._data[p][q] += A._data[p][k]*B._data[k][q];
      }
    }
  }

	std::cout << C << '\n';

	C.send_block(f, 0, C._n);
	std::cout << "Sent matrix C" << '\n';

	close(f);
	std::cout << "Connection closed" << '\n';

	free(fd);
	pthread_detach(pthread_self());
	return NULL;
}

int main (int argc, char ** argv)

{
        const char * server = "0.0.0.0";
        struct sockaddr_in sin;
        int s, f, ret;
	pthread_t tid;
	int optval = 1;

        sin.sin_family = AF_INET;
        sin.sin_port = htons(DEFAULT_PORT);
        ret = inet_aton(server, &sin.sin_addr);
        if (ret == 0) {
		fprintf(stderr, "address %s invalid\n", server);
		return 0;
	}

        s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s < 0) {
		fprintf(stderr, "cannot create socket\n");
		return 0;
	}

        ret = setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
        if (ret != 0) {
                fprintf(stderr, "setsockopt() failed\n");
                return 0;
        }

        ret = bind(s, (struct sockaddr *)&sin, sizeof(sin));
        if (ret != 0) {
		fprintf(stderr, "bind() failed\n");
		return 0;
	}

        ret = listen(s, 10);
        if (ret != 0) {
		fprintf(stderr, "listen() failed\n");
		return 0;
	}

        while (1) {
                f = accept(s, NULL, 0);
                if (f == -1) {
			fprintf(stderr, "accept() failed\n");
			return 0;
		}

		int * fd = new int;
		*fd = f;
		pthread_create(&tid, NULL, hconnect, (void *)fd);
        }

        return 0;
}
