#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <cstring>
#include <cassert>
#include "base.h"
#include <unistd.h>
#include "../matrix/multithread.h"
#include "../matrix/tableau.h"
#include "mat_network.h"

#define SIZE 10

using namespace std;

int main (int argc, char * argv[])

{
        struct sockaddr_in saddr;
        struct hostent * server;
        int s, ret;
	//char buf[BUF_SIZE];

	if (argc == 1) {
		std::cerr << "usage: " << argv[0]
			  << " [ adresse IP/nom du serveur ]" << std::endl;
		return 0;
	}

        s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s < 0) {
                std::cerr << "cannot create socket" << std::endl;
                return 0;
        }

        saddr.sin_family = AF_INET;
        saddr.sin_port = htons(DEFAULT_PORT);
        server = gethostbyname(argv[1]);
        if (server == NULL) {
                std::cerr << "gethostbyname() failed" << std::endl;
		close(s);
                return 0;
        }
        else {
                memcpy(&saddr.sin_addr, server->h_addr, 4);
        }

        ret = connect(s, (struct sockaddr *)&saddr, sizeof(saddr));
        if (ret < 0) {
                std::cerr << "cannot connect to remote server" << std::endl;
                close(s);
                return 0;
        }



    Matrix A(SIZE);
    A.randomize();
    Matrix B(SIZE);
    B.randomize();
    Matrix C(A._m, B._n);

    int i=2,j=5;
    A.send_block(s, i, j);
    //std::cout << "Sent " << j-i << " lines of "<< endl << A << endl;

    B.send_block(s, 0, B._n);
    //std::cout << "Sent " << B._n << " lines of "<< endl << B << endl;

    C = recv_block(s);
    cout << C << endl;




	close(s);
	return 0;
}
