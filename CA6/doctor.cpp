#include "doctor.hpp"
using namespace std;

doctor::doctor(string name)
	:villager(name)
{
	first_heal = true;
	night_role = true;
}

string doctor::type(){return Doctor;}

void doctor::clear_data()
{
	player::clear_data();
	first_heal = true;
}


void doctor::apply_role(player *p , bool day)
{
	player::apply_role(p , day);
	if(!p->get_alive() && day ==false)
		throw Invalid_User_Error("Patient is dead\n");
	else if(!day)
	{
		if(first_heal)
		{
			p->extra_lives++;
			first_heal=false;
		}
		else
			throw Player_Cant_Perform_Role_Error("Doctor has already healed\n");
	}
}