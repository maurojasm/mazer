CC = g++
CFLAGS = -I
TARGET = Mazer
IDIR = ../include
SRCDIR = src/

Mazer: mazer.o maze.o
	g++ -Wall -Wextra -Wpedantic -o p7 main.o bst.o
mazer.o: mazer.cpp src/maze.h
	g++ -Wall -Wextra -Wpedantic -c mazer.cpp
maze.o: src/maze.cpp src/maze_generator.h src/texture.h src/tile.h src/dot.h
	g++ -Wall -Wextra -Wpedantic -c src/maze.cpp
clean:
	rm -f Mazer *.o *~%  