#include "user.hpp"
#include "Exception.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

#define PUBLIC 1
#define PRIVATE 0

user::user()
{
	email = "";
	password = "";
	username = "";
}
user::user(string Email ,  string Username ,string Password )
{
	email = Email;
	password = Password;
	username = Username;
}

string user::get_email(){return email;}

string user::get_password(){return password;}

string user::get_username(){return username;}

playlist* user::find_playlist(int id)
{
	for(int i=0 ;i<playlists.size() ; i++)
	{
		if(playlists[i].get_id() == id)
			return &playlists[i];
	}
	throw Permission_Denied_Error();
}

void user::delete_song(int playlist_id , int song_id)
{
	find_playlist(playlist_id)->delete_Song(song_id);
}

bool user::owns_playlist(int playlist_id)
{
	for(int i=0 ;i<playlists.size() ; i++)
	{
		if(playlists[i].get_id() == playlist_id)
			return true;
	}
	return false;
}

playlist* user::get_specific_playlist(int playlist_id)
{
	playlist* current_playlist = find_playlist(playlist_id);
	return current_playlist;
}

void user::get_public_playlists_songs(int playlist_id)
{
	playlist* current_playlist = find_playlist(playlist_id);
	if(current_playlist->get_privacy_situation() == PRIVATE )
		throw Permission_Denied_Error();
}

void user::add_song(int playlist_id , song* song_to_add)
{
	find_playlist(playlist_id)->add(song_to_add);
}


void user::get_public_playlists()
{
	if(playlists.size() == 0)
		throw Empty_List_Error();
	for(int i=0 ;i<playlists.size() ; i++)
	{
		if(playlists[i].get_privacy_situation() == PUBLIC)
			playlists[i].print_data();
	}
}

vector<playlist> user::get_all_playlists()
{
	return playlists;
}

void user::add_playlist(string name , string privacy , int id)
{
	playlists.push_back(playlist(name ,privacy , id));
}

void user::delete_like(int song_id)
{
	for(int index=0;index<liked_songs.size();index++)
	{
		if(liked_songs[index]->get_id() == song_id)
		{
			liked_songs.erase(liked_songs.begin() + index);
			return;
		}
	}
	throw Bad_Request_Error();
}

bool user::compare(song *s1,song *s2)
{
	return s1->get_id() < s2->get_id();
}

vector<song*> user::get_liked_songs()
{
	if(liked_songs.size()>1)
		sort(liked_songs.begin() , liked_songs.end() , &compare);
	return liked_songs;
}


void user::like(song* song_to_like)
{
	for(int i=0;i<liked_songs.size() ;i++)
	{
		if(liked_songs[i]->get_id() == song_to_like->get_id())
			throw Bad_Request_Error();
	}
	liked_songs.push_back(song_to_like);
}

vector<int> user::get_liked_songs_id()
{
	vector<int> id;
	for(int i=0;i<liked_songs.size() ;i++)
		id.push_back(liked_songs[i]->get_id());
	return id;
}


bool user::has_liked_song(song *Song)
{
	for(int i=0;i<liked_songs.size() ;i++)
	{
		if(liked_songs[i]->get_id() == Song->get_id())
			return true;
	}
	return false;
}

