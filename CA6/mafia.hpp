#ifndef Mafia_H
#define Mafia_H "Mafia_H"
#include "player.hpp"


class mafia : public player{
public:
	void apply_role(player *p , bool day);
	mafia(std::string name);
	std::string type();
};

#endif
