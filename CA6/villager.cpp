#include "villager.hpp"
using namespace std;

villager::villager(string name)
	:player(name)
{
	night_role = false;
}

string villager::type(){return Villager;}
