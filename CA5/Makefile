CC := g++
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: soccerStars.out

soccerStars.out : main.o rsdl.o game.o Ball.o Pawn.o
	$(CC) main.o rsdl.o game.o Ball.o Pawn.o $(CCFLAGS) -o soccerStars.out
	
main.o : main.cpp RSDL/src/rsdl.hpp game.hpp 
	$(CC) -c main.cpp -o main.o

rsdl.o : RSDL/src/rsdl.hpp RSDL/src/rsdl.cpp
	$(CC) -c RSDL/src/rsdl.cpp -o rsdl.o

Ball.o : Ball.hpp Ball.cpp game.hpp Pawn.hpp RSDL/src/rsdl.hpp
	$(CC) -c Ball.cpp -o Ball.o

game.o : game.hpp game.cpp Ball.hpp Pawn.hpp RSDL/src/rsdl.hpp
	$(CC) -c game.cpp -o game.o

Pawn.o : Pawn.hpp Pawn.cpp Ball.hpp game.hpp RSDL/src/rsdl.hpp
	$(CC) -c Pawn.cpp -o Pawn.o
.PHONY:clean
clean:
	rm -r *.o 
