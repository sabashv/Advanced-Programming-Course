#include "playlist.hpp"
#include "Exception.hpp"
#include <exception>
#include <algorithm>
#include <iostream>
using namespace std;

#define PUBLIC 1
#define PRIVATE 0

playlist::playlist(string name_,string privacy_ , int id)
{
	if(privacy_ == "1")
		privacy = PUBLIC;
	if(privacy_ == "0")
		privacy = PRIVATE;
	name = name_;
	playlist_id = id;
}

bool playlist::get_privacy_situation(){return privacy;}

int playlist::get_id(){return playlist_id;}

string playlist::get_name(){return name;}

vector<song*> playlist::get_playlist_songs(){return playlist_songs;}

void playlist::delete_Song(int song_id)
{
	for(int i=0 ; i<playlist_songs.size() ; i++)
	{
		if(playlist_songs[i]->get_id() == song_id)
		{
			playlist_songs.erase(playlist_songs.begin() + i);
			return;
		}
	}
	throw Bad_Request_Error();
}

bool playlist::compare(song *s1,song *s2)
{
	return s1->get_id() < s2->get_id();
}

//  playlist::get_song(int id)
// {
// 	sort(playlist_songs.begin() , playlist_songs.end() ,&compare);
// 	for(int i=0;i<playlist_songs.size();i++)
// 		playlist_songs[i]->print_data();
// }

void playlist::add(song* song_)
{
	playlist_songs.push_back(song_);
}

void playlist::print_data()
{
	string privacy_situation;
	if(privacy == PUBLIC)
		privacy_situation = "public";
	else
		privacy_situation = "private";
	cout<<playlist_id<<" "<<name<<" "<<privacy_situation<<endl;
}