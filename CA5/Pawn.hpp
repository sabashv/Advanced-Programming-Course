#ifndef Pawn_H
#define Pawn_H "Pawn_H"
#include <iostream>
#include "RSDL/src/rsdl.hpp"
#include "Pawn.hpp"
#include "game.hpp"
struct float_point;
class game;
class Pawn {
public:
	Pawn(bool p,int cenetr_x,int center_y,int num);
	bool check_point(float point_x,float point_y);
	void draw(Window* window,float x1,float x2,float x3,float x4,std::string imageaddress);
	void update_pawn(Point mousePosition);
	int move(game *game);
	void update_speed(float new_vx ,float new_vy);

	float get_x(){return x;}
	float get_y(){return y;}
	int get_pawn_num(){return pawn_num;}
	float get_vx(){return vx;}
	float get_vy(){return vy;}
	bool get_player(){return player;}
private:
	void calculate_new_speed(float newpos_x,float newpos_y);
	void update_position(float newX ,float newY);
	bool pawn_is_in_field(float point_x,float point_y);
	void reflect_pawn(float point_x,float point_y);
	float_point find_new_position();
	bool player;
	float vx;
	float vy;
	float x, y;
	int pawn_num;
};
#endif