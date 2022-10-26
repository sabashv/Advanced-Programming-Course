#ifndef Detective_H
#define Detective_H "Detective_H"
#include "villager.hpp"


class detective : public villager{
public:
	void clear_data();
	void apply_role(player *p , bool day);
	detective(std::string name);
	std::string type();
private:
	bool first_ask;
};

#endif
