CC := g++ -std=c++11


all: mafia.out

mafia.out : main.o  player.o mafia.o villager.o doctor.o detective.o EXception.o silencer.o bulletproof.o joker.o godfather.o main_functions.o auxiliary_functions.o
	$(CC) main.o  player.o mafia.o villager.o doctor.o detective.o silencer.o EXception.o bulletproof.o joker.o godfather.o main_functions.o auxiliary_functions.o  -o mafia.out
	
main.o : main.cpp player.hpp main_functions.hpp  EXception.hpp
	$(CC) -c main.cpp -o main.o

main_functions.o : main_functions.hpp main_functions.cpp auxiliary_functions.hpp player.hpp EXception.hpp
	$(CC) -c main_functions.cpp -o main_functions.o

auxiliary_functions.o : auxiliary_functions.hpp auxiliary_functions.cpp player.hpp EXception.hpp
	$(CC) -c auxiliary_functions.cpp -o auxiliary_functions.o

EXception.o : EXception.hpp EXception.cpp 
	$(CC) -c EXception.cpp -o EXception.o

player.o : player.hpp player.cpp EXception.hpp
	$(CC) -c player.cpp -o player.o

villager.o : villager.hpp villager.cpp player.hpp EXception.hpp
	$(CC) -c villager.cpp -o villager.o

mafia.o : mafia.hpp mafia.cpp player.hpp EXception.hpp
	$(CC) -c mafia.cpp -o mafia.o

silencer.o : silencer.hpp silencer.cpp mafia.hpp player.hpp EXception.hpp
	$(CC) -c silencer.cpp -o silencer.o

godfather.o : godfather.hpp godfather.cpp mafia.hpp player.hpp EXception.hpp
	$(CC) -c godfather.cpp -o godfather.o

doctor.o : doctor.hpp doctor.cpp villager.hpp player.hpp EXception.hpp
	$(CC) -c doctor.cpp -o doctor.o

detective.o : detective.hpp detective.cpp villager.hpp player.hpp EXception.hpp
	$(CC) -c detective.cpp -o detective.o

joker.o : joker.hpp joker.cpp player.hpp EXception.hpp
	$(CC) -c joker.cpp -o joker.o

bulletproof.o : bulletproof.hpp bulletproof.cpp villager.hpp player.hpp EXception.hpp
	$(CC) -c bulletproof.cpp -o bulletproof.o

.PHONY:clean
clean:
	rm -r *.o 