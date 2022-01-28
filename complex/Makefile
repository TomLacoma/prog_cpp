main.o: main.cpp
	g++ -c main.cpp -Wall -Werror -O
complex.o: complex.cpp
	g++ -c complex.cpp -Wall -Werror -O
tableau.o: tableau.cpp
	g++ -c tableau.cpp -Wall -Werror -O
main: main.o complex.o tableau.o
	g++ -o main main.o complex.o tableau.o
