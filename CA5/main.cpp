#include "game.hpp"
#include <iostream>
#include "RSDL/src/rsdl.hpp"
using namespace std;
int main()
{
	game Game; 
	Game.get_input();
	Game.start_game();
	return 0;
}