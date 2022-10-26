#ifndef Joker_H
#define Joker_H "Joker_H"
#include "player.hpp"


class joker : public player{
public:
	joker(std::string name);
	std::string type();
};

#endif