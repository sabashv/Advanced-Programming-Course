#ifndef Ball_H
#define Ball_H "Ball_H"
#include <iostream>
#include "RSDL/src/rsdl.hpp"
#include "Ball.hpp"
#include "game.hpp"
#include "Pawn.hpp"
struct float_point;
class Ball{
public:
	Ball();
	void draw(Window* window,float x1,float x2,float x3,float x4,std::string image_address);
	bool check_point(float point_x,float point_y);
	bool move(game *game);
	void update_speed(float new_vx ,float new_vy);

	float get_x(){return x;}
	float get_y(){return y;}
	float get_vx(){return vx;}
	float get_vy(){return vy;}
private:
	void calculate_new_speed(float newpos_x,float newpos_y);
	float_point find_new_position();
	void update_position(float new_x ,float new_y);
	bool ball_is_in_field(float point_x,float point_y);
	void reflect_ball(float point_x,float point_y);
	bool check_goal(float newpos_x,float newpos_y);
	float x,y;
	float vx,vy;
	int pawn_number;
	
};
#endif