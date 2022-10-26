#ifndef MainFunctions_H
#define MainFunctions_H "MainFunctions_H"
#include "auxiliary_functions.hpp"
#include "player.hpp"
#include "villager.hpp"
#include "mafia.hpp"
#include "silencer.hpp"
#include "godfather.hpp"
#include "doctor.hpp"
#include "detective.hpp"
#include "joker.hpp"
#include "bulletproof.hpp"


bool check_if_all_players_have_role(std::vector<player*> *players);

void print_players_and_roles(std::vector<player*> players);

bool check_if_joker_has_died(player *player_to_die);

void swap_character(std::vector<player*> *players ,std::string input , bool *swapped);

void get_game_state(std::vector<player*> *players);

void vote(std::vector<player*> *players , std::string input);

player* day_function(std::vector<player*> *players );

void print_players_awake_in_night(std::vector<player*> *players);

void print_night_report(std::vector<player*> *players , player *player_to_die , int day_number);

player* night_function(std::vector<player*> *players ,int day_number);

bool check_winner(std::vector<player*> *players);

bool start_game(std::vector<player*> *players );

player* assign_role(std::string name , std::string role);

bool game(std::vector<player*> *players);

std::vector<player*> created_game(std::string input);



#endif