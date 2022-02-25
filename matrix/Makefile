main.o: main.cpp
	g++ -c main.cpp -Wall -Werror -O
tableau.o: tableau.cpp
	g++ -c tableau.cpp -Wall -Werror -O
multithread.o: multithread.cpp
	g++ -c multithread.cpp -Wall -Werror -O
main: main.o  tableau.o
	g++ -o main main.o  tableau.o
parallel.o: parallel.cpp
	g++ -c parallel.cpp -Wall -Werror -O
parallel: parallel.o  tableau.o multithread.o
	g++ -o  parallel parallel.o  tableau.o multithread.o -pthread
test.o: test.cpp
	g++ -c test.cpp -Wall -Werror -O
test: test.o  tableau.o multithread.o
	g++ -o  test test.o  tableau.o multithread.o -pthread
