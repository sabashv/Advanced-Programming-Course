#ifndef AuxiliaryFunctions_H
#define AuxiliaryFunctions_H "AuxiliaryFunctions_H"
#include "player.hpp"

std::vector<std::string> split(std::string text); 

bool sort_based_on_ASCII(player *p1 , player *p2);

player* find_player(std::vector<player*> *players , std::string name);

int find_player_index(std::vector<player*> *players , std::string name);

bool sort_based_on_votes(player *p1 , player *p2);

void clear_votes(std::vector<player*> *players);

player* calculate_votes(std::vector<player*> *players);


#endif
