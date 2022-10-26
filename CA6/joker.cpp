#include "joker.hpp"
using namespace std;


joker::joker(string name)
	:player(name)
{
	night_role = false;
}

string joker::type(){return Joker;}
