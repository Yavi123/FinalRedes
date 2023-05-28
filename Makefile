CC=g++
CFLAGS=-g -I. -std=c++11

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
OBJ = $(patsubst %.cpp,%.o,$(call rwildcard,.,*cpp))
LIBS=-I/usr/include/SDL2 -lSDL2 -lSDL2_image

%.o: %.cpp
	$(CC) -g -c -o $@ $< $(CFLAGS) $(LIBS)

all: main

main: $(OBJ)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJ) *.out
