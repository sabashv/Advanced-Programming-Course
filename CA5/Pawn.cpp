// #include <iostream>
// #include <cmath>
// #include "RSDL/src/rsdl.hpp"
// #include <cmath>
// #include <vector>
#include "game.hpp"
#include "Pawn.hpp"
using namespace std;
Pawn::Pawn(bool p,int cenetr_x,int center_y,int num){
		player=p;
		x=cenetr_x;
		y=center_y;
		vx=0;
		vy=0;
		pawn_num=num;
}
void Pawn::update_position(float newX ,float newY) {
	x = newX;
	y = newY;
}
void Pawn::update_speed(float new_vx ,float new_vy) {
	vx = new_vx;
	vy = new_vy;
}
bool Pawn::pawn_is_in_field(float point_x,float point_y)
{
	if( point_x<20 || point_x>780 || point_y <information_box_lenght+counter_radius || point_y >580-counter_radius)
		return false;
	return true;
}
bool Pawn::check_point(float point_x,float point_y){
	float distance=sqrt(pow((x-point_x),2)+pow((y-point_y),2));
	if(distance <= counter_radius+ball_radius)
		return true;
	return false;
}
void Pawn::draw(Window* window,float x1,float x2,float x3,float x4,string imageaddress) {
	window->draw_img(imageaddress,Rectangle(x1,x2,x3,x4));
}
void Pawn::reflect_pawn(float point_x,float point_y)
{
	if( point_x<20){
		point_x=2*20- point_x;
		vx=-vx;
	}
	if( point_x>780){
		point_x=2* 780 - point_x;
		vx=-vx;
	}
	if( point_y <information_box_lenght+counter_radius){
		point_y =2*(information_box_lenght+counter_radius) - point_y ;
		vy= - vy;
	}
	if( point_y >580-counter_radius){
		point_y =2* (580-counter_radius) - point_y ;
		vy=-vy;
	}
	x=point_x;
	y=point_y;
}
int Pawn::move(game *game)
{
	if(vx<10 && -10<vx && -10<vy && vy<10)
	{
		update_speed(0,0);
		return 0;
	}
	float_point new_position= find_new_position();
	while(!pawn_is_in_field(new_position.x,new_position.y))
	{
		reflect_pawn(new_position.x,new_position.y);
		return 0;
	}
	int newpos_situation=game->collision_detection(new_position.x,new_position.y,pawn_num);
	if(newpos_situation>-1)
	{
		if(newpos_situation==10)
		{
			game->kick_ball(pawn_num);
			return 1;
		}
		game->handle_collision(pawn_num,newpos_situation);
		return 0;
	}
	calculate_new_speed(new_position.x,new_position.y);
	update_position(new_position.x,new_position.y);
}
void Pawn::update_pawn(Point mousePosition)
{
	Point pawnPosition;
	pawnPosition.x = x;
	pawnPosition.y = y;
	float_point d;
	d.x = mousePosition.x - pawnPosition.x;
	d.y = mousePosition.y- pawnPosition.y;
	float d_size=sqrt(pow((mousePosition.x - pawnPosition.x) , 2) + pow((mousePosition.y - pawnPosition.y) , 2));
	float initial_speed_x ;
	float initial_speed_y ;
	if(d_size >= ThrowRadius)
	{
		initial_speed_x = (float(d.x)/float(d_size))* MaxInitialSpeed *-1;
		initial_speed_y = (float(d.y)/float(d_size))* MaxInitialSpeed *-1;
	}
	else
	{
		initial_speed_x = (float(d.x)/float(ThrowRadius)*MaxInitialSpeed)*(-1);
		initial_speed_y = (float(d.y)/float(ThrowRadius))*MaxInitialSpeed*-1;
	}
	update_speed(initial_speed_x,initial_speed_y);
}
float_point Pawn::find_new_position()
{
	float xdivision=0.1,ydivision=0.1;
	float acc_x=acceleration;
	float acc_y=acceleration;
	if(vx<0)
		acc_x=-acceleration;
	if(vy<0)
		acc_y=-acceleration;
	float time_x = float(abs(vx))/float(abs(acc_x));
	float time_y = float(abs(vy))/float(abs(acc_y));
	float destination_x=float(acc_x)/float(2) * pow(time_x,2) + vx * time_x +x;
	float destination_y=float(acc_y)/float(2) * pow(time_y,2) + vy * time_y +y;
	float slope = float(destination_y - y)/float(destination_x - x);	
	float_point new_position;
	if(abs(slope) > tan(1.5184))
	{
		if(vy > 0)
			new_position.y = y + ydivision;
		else if(vy < 0)
			new_position.y = y - ydivision;
		if(isinf(slope))
			new_position.x=x;
		else
			new_position.x=(slope/float(new_position.y - y))+x;
	}
	else
	{
		if(vx > 0)
			new_position.x = x + xdivision;
		else if(vx < 0)
			new_position.x = x - xdivision;
		new_position.y=slope*(new_position.x - x)+y;	
    }
    if((vy>0 && new_position.y>destination_y) || (vy<0 && new_position.y<destination_y))
		new_position.y=destination_y;
	if((vx>0 && new_position.x>destination_x) || (vx<0 && new_position.x<destination_x))
		new_position.x=destination_x;
	return new_position;
}
void Pawn::calculate_new_speed(float newpos_x,float newpos_y)
{
	float acc_x=acceleration;
	float acc_y=acceleration;
	if(vx<0)
		acc_x=-acceleration;
	if(vy<0)
		acc_y=-acceleration;
	float curr_speed_x,curr_speed_y;
	curr_speed_x = sqrt(abs(2*acc_x*(newpos_x-x) + pow(vx ,2)));
	if(vx < 0)
		curr_speed_x = -curr_speed_x;
	curr_speed_y = sqrt(abs(2*acc_y*(newpos_y-y) + pow(vy ,2)));
	if(vy < 0)
		curr_speed_y = -curr_speed_y;
	if(-20<curr_speed_x && curr_speed_x <20)
		curr_speed_x=0;
	if(-20<curr_speed_y && curr_speed_y <20)
		curr_speed_y=0;
	update_speed(curr_speed_x,curr_speed_y);
	
}