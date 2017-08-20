CC = g++
CFLAGS = -g -Wall

all: knights

knights: knights.o
	$(CC) $(CFLAGS) -o knights knights.o treap.o

knights.o: knights.cpp
	$(CC) -c knights.cpp

treap.o: treap.cpp
	$(CC) -c treap.cpp

clean:
	-rm -f knights knights.o treap.o 
