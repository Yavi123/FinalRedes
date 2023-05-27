CC=g++
CFLAGS=-g -I. -std=c++11
DEPS = Socket.h Chat.h
OBJ = main.cpp

all: test

test: $(OBJ)
	g++ main.cpp -L./lib -lSDL2main -lSDL2


.PHONY: clean

clean:
	rm -f *.o test