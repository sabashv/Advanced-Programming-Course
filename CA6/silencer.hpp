#ifndef Silencer_H
#define Silencer_H "Silencer_H"
#include "mafia.hpp"


class silencer : public mafia{
public:
	void clear_data();
	void apply_role(player *p , bool day);
	silencer(std::string name);
	std::string type();
private:
	bool first_vote;
};

#endif
