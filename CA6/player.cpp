#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <bits/stdc++.h>
#include "player.hpp"
using namespace std;

player::player(string player_name)
{
	extra_lives=0;
	name = player_name;
	alive = true;
	silenced = false;
	num_of_votes = 0;
}

string player::type(){return Player;}

bool player::get_night_role(){return night_role;}

string player::get_name(){return name;}

string player::get_name_of_votee(){return name_of_votee;}

bool player::get_alive(){return alive;}


player* assign_role(string name , string role);
void player::clear_data()
{
	num_of_votes = 0;
	name_of_votee = "NULL";
	silenced = false;
}
void player::apply_role(player *player , bool day)
{
	if(silenced && day == true)
	 	throw Player_Cant_Perform_Role_Error("Voter is silenced\n");
	 if(player->alive ==false && day == true)
	 	throw Invalid_User_Error("Votee already dead\n");
	 if(day == true)
	 	name_of_votee = player->name;
	 else if(night_role == false )
	 	throw Player_Cant_Perform_Role_Error("User can not wake up during night\n");
}

void player::swap_with(vector<player*> *players,player *p , int user1_index , int user2_index)
{
	string user2_role = p->type();
	string user1_role = type();
	bool user2_silenced=false , user1_silenced = false;
	if(p->silenced)
		user2_silenced = true;
	if(silenced)
		user1_silenced = true;
	int user2_extra_lives = p->extra_lives;
	int user1_extra_lives = extra_lives;
	(*players)[user1_index] = assign_role(name , user2_role);
	if(user2_silenced)
		(*players)[user1_index]->silenced = true;
	(*players)[user1_index]->extra_lives = user2_extra_lives;
	(*players)[user2_index] = assign_role(p->name , user1_role);
	if(user1_silenced)
		(*players)[user2_index] -> silenced = true;
	(*players)[user2_index]->extra_lives = user1_extra_lives;
}

void player::die()
{
	if(extra_lives==0)
		alive = false;
}
