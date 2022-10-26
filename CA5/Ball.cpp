//#include <iostream>
// #include "RSDL/src/rsdl.hpp"
// #include <cmath>
// #include <vector>
#include "game.hpp"
#include "Pawn.hpp"
#include "Ball.hpp"
using namespace std;

Ball::Ball()
{
	vx=0;
	vy=0;
	x=field_width/2-15;
	y=field_lenght/2+information_box_lenght+10;
	pawn_number=-1;
}
void Ball::update_position(float new_x ,float new_y) {
	x = new_x;
	y = new_y;
}
void Ball::draw(Window* window,float x1,float x2,float x3,float x4,string image_address) 
{
	window->draw_img(image_address,Rectangle(x1,x2,x3,x4));

}
void Ball::update_speed(float new_vx ,float new_vy) {
	vx = new_vx;
	vy = new_vy;
}
bool Ball::check_point(float point_x,float point_y){
		float distance=sqrt(pow((x-point_x),2)+pow((y-point_y),2));
		if(distance < ball_radius+counter_radius)
			return true;
		return false;
	}
bool Ball::ball_is_in_field(float point_x,float point_y)
{
	if( point_x<15 || point_x>775 || point_y <information_box_lenght || point_y > 580-15)
		return false;
	return true;
}
void Ball::reflect_ball(float point_x,float point_y)
{
	if( point_x<ball_radius){
		point_x=(2*ball_radius)- point_x;
		vx=-vx;
	}
	if( point_x>field_width-ball_radius-10){
		point_x=2*(field_width-ball_radius-10) - point_x;
		vx=-vx;
	}
	if( point_y <information_box_lenght+ball_radius){
		 point_y =2*(information_box_lenght+ball_radius)-point_y ;
		 vy=-vy;
	}
	if( point_y >480-ball_radius){
		point_y =2*(480-ball_radius) - point_y ;
		vy=-vy;
	}
	x=point_x;
	y=point_y;
}
bool Ball::check_goal(float newpos_x,float newpos_y)
{
	if((newpos_x<ball_radius && newpos_y > information_box_lenght+goal_lenght && newpos_y<information_box_lenght+2*goal_lenght)
		||(newpos_x>field_width-ball_radius && newpos_y > information_box_lenght+goal_lenght && newpos_y<information_box_lenght+2*goal_lenght))
		return true;
	return false;
}
bool Ball::move(game *game)
{
	if((vy<10 &&-10<vy) && (-10<vx && vx<10))
	{
		vy=0;
		vx=0;
		return false;
	}
	float_point new_position= find_new_position();
	if(check_goal(new_position.x,new_position.y))
	   return true;
	while(!ball_is_in_field(new_position.x,new_position.y))
	{
		reflect_ball(new_position.x,new_position.y);
		return false;
	}
	int newpawn_num=game->collision_detection(new_position.x,new_position.y,10);
	if(newpawn_num>-1)
	{
		game->kick_ball(newpawn_num);
		return false;
	}
	calculate_new_speed(new_position.x,new_position.y);
	update_position(new_position.x,new_position.y);
	return false;
}
float_point Ball::find_new_position()
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
void Ball::calculate_new_speed(float newpos_x,float newpos_y)
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