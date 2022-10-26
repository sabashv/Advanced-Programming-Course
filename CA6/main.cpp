#include <iostream>
#include "player.hpp"
#include "EXception.hpp"
#include "main_functions.hpp"
using namespace std;

int main()
{
	while(true)
	{
		string input;
		getline(cin , input);
		try
		{
		 	vector<player*> players=created_game(input);
			if(game(&players)==true)
		 		break;		
		}
		catch(No_Game_Created_Error& ex)
		{
			cout<<ex.what();
			break;
		}
	}
	return 0;
}