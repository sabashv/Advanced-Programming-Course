#ifndef Player_H
#define Player_H "Player_H"
#include <iostream>
#include <vector>
#include "EXception.hpp"
const std::string Mafia = "mafia";
const std::string Villager = "villager";
const std::string Doctor = "doctor";
const std::string Detective = "detective";
const std::string Silencer = "silencer";
const std::string Godfather = "godfather";
const std::string Joker = "joker";
const std::string Bulletproof = "bulletproof";
const std::string Player = "player";

class player{
protected:
	bool  night_role;
	std::string name_of_votee;
public:
	bool silenced;
	int extra_lives;
	int num_of_votes;
	void die();
	player(std::string player_name);
	void swap_with(std::vector<player*> *players,player *player, int  user1_index , int user2_index);
	virtual std::string type();
	virtual void clear_data();
	virtual void apply_role(player *player , bool day);
	bool get_night_role();
	std::string get_name();
	std::string get_name_of_votee();
	bool get_alive();
private:
	std::string name;
	bool alive;
};

#endif
