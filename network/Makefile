CLIENT = client.o multithread.o tableau.o mat_network.o
SERVER = server.o multithread.o tableau.o mat_network.o

all: client server

server: $(SERVER)
	c++ -o server $(SERVER) -lpthread

client: $(CLIENT)
	c++ -o client $(CLIENT)

-include $(CLIENT:.o=.d)
-include $(SERVER:.o=.d)

%.o: %.cpp
	c++ -c $*.cpp -o $*.o -Wall -Wshadow -Werror -O
	c++ -MM $*.cpp > $*.d

multithread.o: ../matrix/multithread.cpp
	c++ -c ../matrix/multithread.cpp -Wall -Werror -O

tableau.o: ../matrix/tableau.cpp
	c++ -c ../matrix/tableau.cpp -Wall -Werror -O
