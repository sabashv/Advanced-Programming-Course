#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <bits/stdc++.h>
#include "main_functions.hpp"
using namespace std;

bool check_if_all_players_have_role(vector<player*> *players)
{
	for(int i = 0 ; i < players->size() ;i++)
	{
		if((*players)[i]->type() == Player)
		{
			return false;
		}
	}
	return true;
}


void print_players_and_roles(vector<player*> players)
{
	for(int i = 0 ; i < players.size() ;i++)
	{
		cout<<players[i]->get_name()<<": "<<players[i]->type()<<endl;
	}
}


bool check_if_joker_has_died(player *player_to_die)
{
	if(player_to_die->type() == Joker && player_to_die->get_alive() == false)
	{
		cout<<"Joker won";
		return true;
	}
	return false;
}

void swap_character(vector<player*> *players ,string input , bool *swapped)
{
	if(*swapped)
		throw Swap_Error("Characters already swapped\n");
	player *user1 = find_player(players , split(input)[1]);
	player *user2 = find_player(players , split(input)[2]);
	if(user1->get_alive() == false || user2->get_alive() == false)
		throw Invalid_User_Error("User is dead\n");
	int user1_index = find_player_index(players , user1->get_name());
	int user2_index = find_player_index(players , user2->get_name());
	user1->swap_with(players , user2 , user1_index , user2_index);
	*swapped = true;
}

void get_game_state(vector<player*> *players)
{
	int number_of_mafias=0,number_of_villager=0;
	for(int i=0 ;i < players->size() ; i++)
	{
		if((*players)[i]->get_alive() == true )
		{
			if((*players)[i]->type() == Mafia || (*players)[i]->type() == Godfather || (*players)[i]->type() == Silencer)
				number_of_mafias++;
			else if((*players)[i]->type() != Joker)
				number_of_villager++;
		}
	}
	cout<<"Mafia = "<<number_of_mafias<<endl<<"Villager = "<<number_of_villager<<endl;
}

void vote(vector<player*> *players , string input)
{
	if(split(input)[0] == "swap_character")
		throw Swap_Error("Votting in progress\n");
	player *voter = find_player(players , split(input)[0]);
	player *votee = find_player(players , split(input)[1]);
	voter->apply_role(votee , true);
}


player* day_function(vector<player*> *players )
{
	bool swapped = false;
	while(true)
	{
		string input;
		getline(cin , input);
		if(input=="end_vote")
		{
			return (calculate_votes(players));
		}
		else if(input=="get_game_state")
		{
			get_game_state(players);
			continue;
		}
		try
		{
			if(split(input)[0] == "swap_character")
				swap_character(players ,  input , &swapped);
			else if(input == "start_game")
				throw Invalid_Command_Error("Game has already started\n");
			else
				vote(players , input);
		}
		catch(Swap_Error& ex)
		{
			cout<<ex.what();
		}
		catch(Invalid_Command_Error &ex)
		{
			cout<<ex.what();	
		}
		catch(Invalid_User_Error &ex)
		{
			cout<<ex.what();
		}
		catch(Player_Cant_Perform_Role_Error &ex)
		{
			cout<<ex.what();
		}
	}

 }
  
void print_players_awake_in_night(vector<player*> *players)
{
	vector<player*> players_to_print;
	for(int i=0;i<players->size();i++)
	{
		if((*players)[i]->get_alive() == true && (*players)[i]->get_night_role() == true )
		  	 players_to_print.push_back((*players)[i]);
	}
	for(int i=0; i < players_to_print.size() ; i++)
		cout<<players_to_print[i]->get_name()<<": "<<players_to_print[i]->type()<<endl;
}

void print_night_report(vector<player*> *players , player *player_to_die , int day_number)
{
	cout<<"Day "<<day_number<<endl;
	if(!player_to_die->get_alive())
		cout<<player_to_die->get_name()<<" was killed\n";
	vector<player*> silenced_players;
	for(int i=0 ;i < players->size() ; i++)
	{
		if((*players)[i]->get_alive() == true && (*players)[i]->silenced == true )
		{
			silenced_players.push_back((*players)[i]);
		}
	}
	if(silenced_players.size() > 0)
		cout<<"Silenced";
	sort(&silenced_players[0] , &silenced_players[silenced_players.size()] , sort_based_on_ASCII);
	for(int i=0; i < silenced_players.size() ; i++)
		cout<<" "<<silenced_players[i]->get_name();
	cout<<endl;
}

player* night_function(vector<player*> *players ,int day_number)
{
	cout<<"Night "<<day_number<<endl;
	print_players_awake_in_night(players);
	 string input;
	while(true)
	{
		getline(cin , input);
	    if(input=="end_night")
		 	return calculate_votes(players);
		if(input=="get_game_state")
		{
			get_game_state(players);
			continue;
		}
		try
		{
			if(split(input)[0] == "swap_character")
				throw Swap_Error("Canr't swap before end of night\n");
			player *first_player = find_player(players , split(input)[0]);
			player *second_player = find_player(players , split(input)[1]);
			first_player->apply_role(second_player , false);
    	}
   	 	catch(Swap_Error& ex)
		{
			cout<<ex.what();
		}
		catch(Invalid_Command_Error &ex)
		{
			cout<<ex.what();	
		}
		catch(Invalid_User_Error &ex)
		{
			cout<<ex.what();
		}
		catch(Player_Cant_Perform_Role_Error &ex)
		{
			cout<<ex.what();
		}
    }
}

bool check_winner(vector<player*> *players)
{
	int number_of_mafias=0,number_of_villager=0;
	for(int i=0 ;i < players->size() ; i++)
	{
		if((*players)[i]->get_alive() == true )
		{
			if((*players)[i]->type() == Mafia || (*players)[i]->type() == Godfather || (*players)[i]->type() == Silencer)
				number_of_mafias++;
			else if((*players)[i]->type() != Joker)
				number_of_villager++;
		}
	}
	if (number_of_mafias==0)
	{
		cout<<"Villagers won";
		return true;
	}
	if (number_of_villager <= number_of_mafias)
	{
		cout<<"Mafia won";
		return true;
	}
	return false;
}

bool start_game(vector<player*> *players )
{
	if(!check_if_all_players_have_role(players ))
		throw Player_Has_No_Role_Error();
	print_players_and_roles(*players);
	cout<<"Ready? Set! Go.\n";
	int day_number=1;
	cout<<"Day "<<day_number<<endl;
	while(true)
	{
		player *player_to_die_in_day=day_function(players);
		player_to_die_in_day->die();
		if(player_to_die_in_day->get_alive() == false)
			cout<<player_to_die_in_day->get_name()<<" died\n";
		if(check_if_joker_has_died(player_to_die_in_day) == true)
			return true;
		if(check_winner(players))
			return true;
		clear_votes(players);
		player *player_to_die_in_night=night_function(players ,day_number);
		cout<<"Mafia tried to kill "<<player_to_die_in_night->get_name()<<endl;
		player_to_die_in_night->die();
		day_number++;
		print_night_report(players , player_to_die_in_night , day_number);
		if(check_winner(players))
			return true;
	}
}
 

 player* assign_role(string name , string role)
{
	if(role == Mafia)
	   return (new mafia(name));
	if(role == Joker)
		 return (new joker(name));
	if(role == Silencer)
		 return (new silencer(name));
	if(role == Godfather)
		 return (new godfather(name));
	if(role == Doctor)
		 return (new doctor(name));
	if(role == Detective)
		 return (new detective(name));
	if(role == Bulletproof)
		 return (new bulletproof(name));
	if(role == Villager)
		 return (new villager(name));
}

bool game(vector<player*> *players)
{

	while(true)
	{
		string input;
		getline(cin , input);
		if(split(input)[0]=="assign_role")
		{
			try
			{
				int player_number= find_player_index(players , split(input)[1]);
				(*players)[player_number]=assign_role(split(input)[1],split(input)[2]);
			}
			catch(Invalid_User_Error& ex)
			{
				cout<<ex.what();
			}

		}
		else if( input == "start_game" )
		{
			try
			{
				if(start_game(players))
					return true;
			}
	   		catch(Player_Has_No_Role_Error& ex)
			{
				cout<<ex.what();
			}
		}
	}
}

vector<player*> created_game(string input)
{
	if(split(input)[0]=="create_game")
	{
		vector<string> player_names = split(input);
		vector<player*> players;
		for(int i=1 ; i<player_names.size() ; i++)
		{
			player *p=new player(player_names[i]);
			players.push_back(p);
		}
		return players;
	}
	throw No_Game_Created_Error();
}