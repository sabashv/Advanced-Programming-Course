#ifndef Bulletproof_H
#define  Bulletproof_H "Bulletproof_H"
#include "villager.hpp"


class bulletproof : public villager{
public:
	bulletproof(std::string name);
	std::string type();
};

#endif