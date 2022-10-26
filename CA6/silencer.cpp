#include "silencer.hpp"
using namespace std;


silencer::silencer(string name)
	:mafia(name)
{
	first_vote = true;
}

string silencer::type(){return Silencer;}
void silencer::clear_data()
{
	player::clear_data();
	first_vote = true;
}
void silencer::apply_role(player *p , bool day)
{
	player::apply_role(p , day);
	if(!p->get_alive() && day == false)
		throw Invalid_User_Error("Person is dead\n");
	else if(!day)
	{
		if(first_vote)
		{
			p->silenced = true;
			first_vote = false;
		}
		else
			name_of_votee = p->get_name();
	}
}