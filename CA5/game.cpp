#include <iostream>
#include "RSDL/src/rsdl.hpp"
#include <cmath>
#include <vector>
#include "game.hpp"
#include "Pawn.hpp"
#include "Ball.hpp"
using namespace std;
#define counter_radius 20
#define Player1 0
#define Player2 1
#define ThrowRadius 60
#define MaxInitialSpeed 500
#define acceleration -300
#define m1 2
#define m2 1
#define ball_radius 15
#define field_width 800
#define field_lenght 480
#define information_box_lenght 50
#define information_box_width 800
#define goal_lenght 160
#define enter 13
#define game_speed 3
#define ball_image_address "ball.png"
#define font_address "FreeSans-LrmZ.ttf"
#define field_image_address "field.jpg"
#define pawn1_image_address "Player1.png"
#define pawn2_image_address "Player2.png"
#define circle_image_address "circle.png"
game::game()
{
	P1.goals=0;
	P2.goals=0;
	P1.rounds=0;
	P2.rounds=0;
}
void game::information_box()
{
	window->fill_rect(Rectangle(0,0,field_width,information_box_lenght),RGB(67,66,66));
	window->draw_rect(Rectangle(0,0,field_width,information_box_lenght));
	window->draw_img(ball_image_address,Rectangle(390,5,20,20));
	string rounds=to_string(P1.rounds)+" / "+to_string(P2.rounds);
	window->show_text(rounds, Point(380,20),BLACK, font_address, 24);
	window->show_text("Player1", Point(5,10),BLACK, font_address, 24);
	window->show_text("Player2", Point(710,10),BLACK, font_address, 24);
	window->show_text(to_string(P1.goals), Point(330,10),BLACK,font_address,30);
	window->show_text(to_string(P2.goals), Point(470,10),BLACK, font_address,30);
	window->draw_rect(Rectangle(90,15,100,20));
	window->draw_rect(Rectangle(600,15,100,20));	
}
void game::primitive_field()
{
	Pawnvec.clear();
	Pawnvec.push_back(new Pawn(Player1,field_width/20+20,field_lenght/2+information_box_lenght+25,0));
	Pawnvec.push_back(new Pawn(Player1,field_width/4-20,field_lenght/4+information_box_lenght+20,1));
	Pawnvec.push_back(new Pawn(Player1,field_width/4-20,field_lenght/2+information_box_lenght+field_lenght/4+20,2));
	Pawnvec.push_back(new Pawn(Player1,field_width/2-80,field_lenght/2+information_box_lenght-field_lenght/8+20,3));
	Pawnvec.push_back(new Pawn(Player1,field_width/2-80,field_lenght/2+information_box_lenght+field_lenght/8+20,4));
	Pawnvec.push_back(new Pawn(Player2,field_width-(field_width/20)-20,field_lenght/2+information_box_lenght+25,5));
	Pawnvec.push_back(new Pawn(Player2,field_width-field_width/4+20,field_lenght/4+information_box_lenght+20,6));
	Pawnvec.push_back(new Pawn(Player2,field_width-field_width/4+20,field_lenght/2+information_box_lenght+field_lenght/4+20,7));
	Pawnvec.push_back(new Pawn(Player2,field_width/2+80,field_lenght/2+information_box_lenght-field_lenght/8+20,8));
	Pawnvec.push_back(new Pawn(Player2,field_width/2+80,field_lenght/2+information_box_lenght+field_lenght/8+20,9));
	Ball *b = new Ball();
	ball= b;
}
void game::reset_screen()
{
	window->clear();
	window->draw_img(field_image_address, Rectangle(0,information_box_lenght,field_width,field_lenght+information_box_lenght));
	for(int i=0;i<5;i++)
		Pawnvec[i]->draw(window,Pawnvec[i]->get_x()-counter_radius,Pawnvec[i]->get_y()-counter_radius,counter_radius*2,counter_radius*2,pawn1_image_address);
	for(int i=5;i<10;i++)
		Pawnvec[i]->draw(window,Pawnvec[i]->get_x()-counter_radius,Pawnvec[i]->get_y()-counter_radius,counter_radius*2,counter_radius*2,pawn2_image_address);
	ball->draw(window,ball->get_x(),ball->get_y(),ball_radius*2,ball_radius*2,ball_image_address);
	information_box();
}
Pawn* game::find_pawn(Point mousePosition)
{
	for(int i=0;i<10;i++)
	{
	 	if(Pawnvec[i]->check_point(mousePosition.x,mousePosition.y))
	 		return Pawnvec[i];
	}
}
bool game::mousePosition_is_valid(Point mousePosition,bool turn)
{
	if(find_pawn(mousePosition)!=NULL)
	{
	  	if(find_pawn(mousePosition)->get_player()==turn)
	 		return true;
	}
	 return false;
}
void game::time_line(float time,bool turn)
{
	if(turn==Player1)
		window->fill_rect(Rectangle(90,15,10+time,20),BLUE);
	else
		window->fill_rect(Rectangle(600,15,10+time,20),BLUE);
}
void game::draw_speed_circle(Pawn *current_pawn)
{
	Point center;
	center.x=current_pawn->get_x();
	center.y=current_pawn->get_y();
	Point mouse_curr_pos=get_current_mouse_position();
	double slope=(float(mouse_curr_pos.y-center.y)/float(mouse_curr_pos.x - center.x));
	int radius=sqrt(pow(mouse_curr_pos.x - center.x,2)+pow(mouse_curr_pos.y-center.y,2));
	if(radius>ThrowRadius)
		radius=ThrowRadius;
	float x_prime;
	float y_prime ;
	if(isinf(slope))
	{
		x_prime=center.x;
		if(mouse_curr_pos.y<center.y)
		{
			y_prime = center.y+radius;
		}
		else if(mouse_curr_pos.y<center.y)
			y_prime = center.y-radius;
	}
	else
	{
	x_prime = sqrt(float(pow(radius,2))/float((pow(slope,2)+1)))+center.x;
	if(mouse_curr_pos.x>center.x)
		x_prime = - sqrt(float(pow(radius,2))/float((pow(slope,2)+1)))+center.x;
	y_prime = slope * (x_prime - center.x) + center.y;
    }
	window->draw_img(circle_image_address,Rectangle(center.x - radius , center.y - radius , radius *2 ,radius *2));
	window->draw_line(Point(center.x,center.y),Point(x_prime,y_prime),BLACK );
	window->fill_circle(Point(x_prime,y_prime),5,BLACK );
	return;	
}
int game::collision_detection(float x,float y,int pawn_num)
{
	if(ball->check_point(x,y) && pawn_num!=10 )
		return 10;
	for(int i=0;i<10;i++)
	{
		if(i != pawn_num)
		{
			if(Pawnvec[i]->check_point(x,y))
				return i;
		}
	}
	return -1;
}
void game::handle_collision(int first_pawn_num , int second_pawn_num)
{
	float deltav_x =Pawnvec[first_pawn_num]->get_vx() -Pawnvec[second_pawn_num]->get_vx();
	float deltav_y =Pawnvec[first_pawn_num]->get_vy() - Pawnvec[second_pawn_num]->get_vy();
	float deltax_x=Pawnvec[first_pawn_num]->get_x() - Pawnvec[second_pawn_num]->get_x();
	float deltax_y=Pawnvec[first_pawn_num]->get_y() - Pawnvec[second_pawn_num]->get_y();
	float deltax_size=(pow(deltax_x,2)+pow(deltax_y,2));
	float inner_product=((deltav_x*deltax_x)+(deltav_y*deltax_y));
	float v1_prime_x = Pawnvec[first_pawn_num]->get_vx() -
	((float(2*m1)/float(m1+m1)) * (float(inner_product)/float(deltax_size)) * deltax_x);
	float v1_prime_y = Pawnvec[first_pawn_num]->get_vy() -
	((float(2*m1)/float(m1+m1)) * (float(inner_product)/float(deltax_size)) * deltax_y);
	float v2_prime_x = Pawnvec[second_pawn_num]->get_vx() -
	((float(2*m1)/float(m1+m1)) * (float(inner_product)/float(deltax_size)) * (-1)*deltax_x);
	float v2_prime_y = Pawnvec[second_pawn_num]->get_vy() -
	((float(2*m1)/float(m1+m1)) * (float(inner_product)/float(deltax_size)) * (-1)*deltax_y);
	Pawnvec[first_pawn_num]->update_speed(v1_prime_x,v1_prime_y);
	Pawnvec[second_pawn_num]->update_speed(v2_prime_x,v2_prime_y);
}
void game::kick_ball(int pawn_num)
{
	float deltav_x =Pawnvec[pawn_num]->get_vx() - ball->get_vx();
	float deltav_y =Pawnvec[pawn_num]->get_vy() - ball->get_vy();
	float deltax_x=Pawnvec[pawn_num]->get_x() - ball->get_x();
	float deltax_y=Pawnvec[pawn_num]->get_y() - ball->get_y();
	float deltax_size=(pow(deltax_x,2)+pow(deltax_y,2));
	float inner_product=((deltav_x*deltax_x)+(deltav_y*deltax_y));
	float v1_prime_x = Pawnvec[pawn_num]->get_vx() -
	((float(2*m2)/float(m1+m2)) * (float(inner_product)/float(deltax_size)) * deltax_x);
	float v1_prime_y = Pawnvec[pawn_num]->get_vy() -
	((float(2*m2)/float(m1+m2)) * (float(inner_product)/float(deltax_size)) * deltax_y);
	float v2_prime_x = ball->get_vx() -
	((float(2*m1)/float(m1+m2)) * (float(inner_product)/float(deltax_size)) * (-1)*deltax_x);
	float v2_prime_y = ball->get_vy() -
	((float(2*m1)/float(m1+m2)) * (float(inner_product)/float(deltax_size)) * (-1)*deltax_y);
	Pawnvec[pawn_num]->update_speed(v1_prime_x,v1_prime_y);
	ball->update_speed(v2_prime_x,v2_prime_y);
}

bool game::move()
{
	int number_of_moves=0;
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			if(Pawnvec[j]->get_vx()!=0 || Pawnvec[j]->get_vy()!=0)
			{
				Pawnvec[j]->move(this);
				number_of_moves++;
				i=0;
			}
			if(number_of_moves>10000)
				return false;
		}
		if(ball->get_vx()!=0 || ball->get_vy()!=0)
		{
			if(ball->move(this))
				return true;
			i=0;
			number_of_moves++;
			if(number_of_moves>10000)
				return false;
		}
		if(number_of_moves%game_speed==0)
		{
			reset_screen();
			window->update_screen();
	    }
	 }	
   return false;
}
bool game::get_mouse_info(float time,bool turn)
{
	while(window->has_pending_event()) {
		Event event = window->poll_for_event();
		if(event.get_type()==Event::EventType::LCLICK) {
			if(mousePosition_is_valid( event.get_mouse_position(),turn))
			{
				Pawn *current_pawn=find_pawn( event.get_mouse_position());
				while(window->poll_for_event().get_type() != Event::EventType::LRELEASE)
	            {
					reset_screen();
					draw_speed_circle(current_pawn);	
					time+=0.01;
					if(time>90)
						return true;
					time_line(time,turn);
					window->update_screen();
				}
				Point mousePosition = get_current_mouse_position();
				current_pawn->update_pawn(mousePosition);		
				return true;
			}
		}
		if(event.get_type()==Event::EventType::QUIT) {
				exit(0);
				break;
		}
	return false;
    }
}
void game::get_move_from_player(bool turn)
{
	float time=0;
	while(time<100)
	{
		window->clear();
	    reset_screen();
		time_line(time,turn);
		window->update_screen();
		time+=0.01;
		if(time==90)
			return ;
		if(get_mouse_info(time,turn)==true)
			return;
   }
}
bool game::goal()
{
	window->draw_rect(Rectangle(200,280,400,90),BLACK);
	window->show_text("GOAL!!!!!!!", Point(220,290),BLACK, font_address , 34);
	window->update_screen();
	delay(1000);
	if(ball->get_x()<20)
	{
		P2.goals++;
		if(number_of_goals==P2.goals)
		{
			P2.goals=0;
			P2.rounds++;
		}
		return Player2;
	}
	else
	{
		P1.goals++;
		if(number_of_goals==P1.goals)
		{
			P1.goals=0;
			P1.rounds++;
		}
		return Player1;
	}
}
bool game::check_winner()
{
	if(P1.rounds+P2.rounds==number_of_rounds)
	{
		string output;
		if(P1.rounds>P2.rounds)
			output="Player1 Has Won";
		else if(P2.rounds>P1.rounds)
			output="Player2 Has Won";
		else
			output="No winner";
		window->draw_rect(Rectangle(200,280,400,90),BLACK);
	    window->show_text(output, Point(220,290),BLACK, font_address , 34);
	    window->update_screen();
	    delay(10000);
	    return true;
	}
	return false;
}
void game::start_game()
{
	bool turn=Player1;
	primitive_field();
	while(true)
	{
		get_move_from_player(turn);
		if(move())
		{
			if(goal()==Player2)
				turn=Player2;
			else
				turn=Player1;
			primitive_field();
			reset_screen();
			window->update_screen();
		}
		if(check_winner()==true)
			return;
		if(turn)
			turn=Player1;
		else
			turn=Player2;
		delay(100);
    }
}
void game::get_number_of_rounds()
{
	window->show_text("Entetr number of rounds", Point(220,290),BLACK, font_address , 34);
	window->show_text("(then press ENTER)", Point(300,330),BLACK, font_address , 20);
	window->update_screen();
	char pressed_Char;
	while(true){
    	Event event = window->poll_for_event();
		if(event.get_type() == Event::KEY_PRESS ) {
  			pressed_Char = event.get_pressed_key();
  			if(pressed_Char!=enter)
    			number_of_rounds=pressed_Char-48; 
			if(pressed_Char==enter)
			{
				window->clear();
			    return;
			}
				
    	}
    }
}
void game::get_number_of_goals()
{
	window->draw_img(field_image_address , Rectangle(0,information_box_lenght,field_width,field_lenght+information_box_lenght));
	window->draw_rect(Rectangle(200,280,400,90),BLACK);
	window->show_text("Entetr number of Goals", Point(220,290), BLACK, font_address , 34);
	window->show_text("(then press ENTER)", Point(300,330),BLACK, font_address , 20);
	window->update_screen();
	char pressed_Char;
	while(true){
    	Event event = window->poll_for_event();
		if(event.get_type() == Event::KEY_PRESS ) {
  			pressed_Char = event.get_pressed_key();
  			if(pressed_Char!=enter)
    			number_of_goals=pressed_Char-48;
    		if(pressed_Char==enter)
    		{
    			window->clear();
				return;
    		}
		}
	}
}
void game::get_input()
{
	window->draw_img(field_image_address , Rectangle(0,information_box_lenght,field_width,field_lenght+information_box_lenght));
	window->draw_rect(Rectangle(200,280,400,90),BLACK);
	window->update_screen();
	get_number_of_rounds();
    get_number_of_goals();
	window->draw_img(field_image_address , Rectangle(0,information_box_lenght,field_width,field_lenght+information_box_lenght));
	window->show_text("START", Point(320,290),BLACK, font_address , 54);
	window->update_screen();
	delay(1000);
    return; 
}