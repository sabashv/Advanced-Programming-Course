#include "bulletproof.hpp"
using namespace std;

bulletproof::bulletproof(string name)
	:villager(name)
{
	extra_lives = 1;
	night_role = false;
}

string bulletproof::type(){return Bulletproof;}
