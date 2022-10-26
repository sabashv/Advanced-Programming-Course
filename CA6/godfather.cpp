#include "godfather.hpp"
using namespace std;

string godfather::type(){return Godfather;}

godfather::godfather(string name)
	:mafia(name){;}

void godfather::apply_role(player *p , bool day)
{
	player::apply_role(p , day);
	if(!day)
		name_of_votee = p->get_name();
}

