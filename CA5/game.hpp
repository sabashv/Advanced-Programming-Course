#ifndef game_H
#define game_H "game_H"
#include <iostream>
#include <vector>
#include "RSDL/src/rsdl.hpp"
#include "Ball.hpp"
#include "Pawn.hpp"
#include "game.hpp"
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
struct float_point{
	float x;
	float y;
};
struct player
{
	int goals;
	int rounds;
};
class game{
public:
	game();

	void start_game();
	void get_input();
	int collision_detection(float x,float y,int pawn_num);
	void handle_collision(int first_pawn_num , int second_pawn_num);
	void kick_ball(int pawn_num);
	Window *window = new Window(800,580, "SOCCER STARS");
	std::vector<Pawn*> get_Pawnvec(){return Pawnvec;}
	Ball* get_ball(){return ball;}
private:
	void time_line(float time,bool turn);
	void reset_screen();
	bool move();
	void information_box();
	bool mousePosition_is_valid(Point mousePosition,bool turn);
	void draw_speed_circle(Pawn* current_pawn);
	void primitive_field();
	void get_number_of_rounds();
	void get_number_of_goals();
	bool check_winner();
	bool goal();
	void get_move_from_player(bool turn);
	bool get_mouse_info(float time,bool turn);
	Pawn* find_pawn(Point mousePosition);
	int number_of_rounds,number_of_goals;
	player P1,P2;
	std::vector<Pawn*> Pawnvec;
	Ball *ball;
};
#endif