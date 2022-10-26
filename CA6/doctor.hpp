#ifndef Doctor_H
#define Doctor_H "Doctor_H"
#include "villager.hpp"



class doctor : public villager{
public: 
	void clear_data();
	void apply_role(player *p , bool day);
	doctor(std::string name);
	std::string type();
private:
	bool first_heal;
};

#endif
