CC=g++
CFLAGS=-g -I. -std=c++11

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
OBJ = $(patsubst %.cpp,%.o,$(call rwildcard,.,*cpp))
LIBS=-lSDL2 -I/usr/include/SDL2

%.o: %.cpp
	$(CC) -g -c -o $@ $< $(CFLAGS) $(LIBS)

all: main.out

main.out: $(OBJ)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJ) *.out