#include "song.hpp"
#include "Exception.hpp"
#include <exception>
#include <algorithm>
#include <iostream>
using namespace std;

song::song(string id_ , string title_ , string artist_ , string year_ , string link_)
{
	id = stoi(id_);
	title = title_;
	artist = artist_;
	release_year = stoi(year_);
	link = link_;
	num_of_likes = 0;
	num_of_playlists = 0;
}

int song::get_id(){return id;}

string song::get_artist(){return artist;}

string song::get_title(){return title;}

int song::get_release_year(){return release_year;}

string song::get_link(){return link;}

int song::get_num_of_likes(){return num_of_likes;}

int song::get_num_of_playlists(){return num_of_playlists;}

void song::increase_number_of_likes(){num_of_likes++;}

void song::increase_number_of_playlists(){num_of_playlists++;}

void song::decrease_number_of_likes(){num_of_likes--;}

void song::decrease_number_of_playlists(){num_of_playlists--;}




