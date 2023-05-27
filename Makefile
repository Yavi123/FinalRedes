CC=g++
CFLAGS=-g -I. -std=c++11
DEPS = 
OBJ = main.o
LIBS=-lpthread -lSDL2 -I"/usr/include/SDL2"

%.o: %.cpp $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS) $(LIBS)

all: main.out

main.out: $(OBJ)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o a.out
