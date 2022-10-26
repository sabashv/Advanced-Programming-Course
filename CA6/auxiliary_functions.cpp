#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <exception>
#include <bits/stdc++.h>
#include "auxiliary_functions.hpp"
using namespace std;

vector<string> split(string text)
{
	vector<string> words;
	stringstream textstream(text);
	string word;
	while(textstream>>word)
		words.push_back(word);
	return words;
}


bool sort_based_on_ASCII(player *p1 , player *p2)
{
	
	return p1->get_name() <= p2->get_name();
}


player* find_player(vector<player*> *players , string name)
{
	for(int i=0;i<players->size();i++)
	{
		if((*players)[i]->get_name() == name)
		{	
		    return (*players)[i];	 
		}
	}
	throw Invalid_User_Error("User not joined\n");
}

int find_player_index(vector<player*> *players , string name)
{
	for(int i=0;i<players->size();i++)
	{
		if((*players)[i]->get_name() == name)
		{	
		    return i;	 
		}
	}
	throw Invalid_User_Error("User not joined\n");
}


bool sort_based_on_votes(player *p1 , player *p2)
{
	if(p1->num_of_votes != p2->num_of_votes)
		return p1->num_of_votes > p2->num_of_votes;
	else
		return p1->get_name() < p2->get_name();
}

void clear_votes(vector<player*> *players)
{
	for(int i=0;i<players->size();i++)
	{
		(*players)[i]->clear_data();
	}
}

player* calculate_votes(vector<player*> *players)
{
	for(int i=0;i<players->size();i++)
	{
		for(int j=0; j < players->size() ; j++)
		{
			if((*players)[i]->get_name_of_votee() == (*players)[j]->get_name() && (*players)[j]->get_alive() == true)
		  	 	(*players)[j]->num_of_votes ++;
		}
	}
	vector <player*> sorted_players;
	for(int i=0;i<players->size();i++)
	{
		sorted_players.push_back((*players)[i]);
	}
	sort(&sorted_players[0] , &sorted_players[players->size()] , sort_based_on_votes);
	player *player_to_die = find_player(players , sorted_players[0]->get_name());
	return player_to_die;
} 
