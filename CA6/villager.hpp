#ifndef Villager_H
#define Villager_H "Villager_H"
#include "player.hpp"

class villager : public player{
public:
	villager(std::string name);
	std::string type();
};

#endif
