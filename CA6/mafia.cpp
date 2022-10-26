#include "mafia.hpp"
using namespace std;

mafia::mafia(string name)
	:player(name)
{
	night_role = true;
}


string mafia::type(){return Mafia;}


void mafia::apply_role(player *p , bool day)
{
	player::apply_role(p , day);
	if(!day)
		name_of_votee = p->get_name();
}