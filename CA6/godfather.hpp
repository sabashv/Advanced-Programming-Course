#ifndef Godfather_H
#define Godfather_H "Godfather_H"
#include "mafia.hpp"


class godfather : public mafia{
public:
	void apply_role(player *p , bool day);
	godfather(std::string name);
	std::string type();
};

#endif