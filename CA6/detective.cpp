#include "detective.hpp"
using namespace std;

detective::detective(string name)
	:villager(name)
{
	first_ask = true;
	night_role = true;
}
string detective::type(){return Detective;}

void detective::clear_data()
{
	player::clear_data();
	first_ask = true;
}
void detective::apply_role(player *p , bool day)
{
	player::apply_role(p , day);
	if(!p->get_alive() && day==false)
		throw Invalid_User_Error("Suspect is dead\n");
	else if(!day)
	{
		if(first_ask)
		{
			if(p->type()==Mafia || p->type()==Silencer)
				cout<<"Yes\n";
			else
				cout<<"No\n";
			first_ask = false;
		}
		else
			throw Player_Cant_Perform_Role_Error("Detective has already asked\n");
	}
}