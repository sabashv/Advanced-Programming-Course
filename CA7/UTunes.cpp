#include "UTunes.hpp"


#include "Exception.hpp"
#include "recommendation.hpp"
#include "CSVReader.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

#define PUBLIC 1
#define PRIVATE 0
const string USERNAME = "username";
const string EMAIL = "email";
const string PASSWORD = "password";
const string TIME = "time";
const string COMMENT = "comment";
const string NAME = "name";
const string PRIVACY = "privacy";
const string ID = "id";
const string SONG_ID = "song_id";
const string PLAYLIST_ID = "playlist_id";
const string MAX_YEAR = "max_year";
const string MIN_YEAR = "min_year";
const string MAX_LIKE = "max_like";
const string MIN_LIKE = "min_like";
const string ARTIST = "artist";
const string OK = "OK";
const string YEAR = "year";
const string LIKE = "like";
const string COUNT = "count";

UTunes::UTunes(string songs_file_address , string liked_songs_file_address)
{
	extract_songs_info(songs_file_address);
	extract_liked_songs_info(liked_songs_file_address);
	current_user = new user();
	next_playlist_id = 1;
	
}


void UTunes::extract_songs_info(string file_address)
{
	CSVReader read_file(file_address,",");
    vector<vector<string>> songs_List = read_file.getData();
	for(int row=1 ; row<songs_List.size() ; row++)
		songs.push_back(song(songs_List[row][0],songs_List[row][1],songs_List[row][2],songs_List[row][3],songs_List[row][4]));
	
}



void UTunes::extract_liked_songs_info(string file_address)
{
	CSVReader read_file(file_address,",");
    vector<vector<string>> liked_songs_List = read_file.getData();

	for(int row=1 ; row<liked_songs_List.size() ; row++)
	{
		if(user_already_exists(liked_songs_List[row][0]))
		{
			song *curr_song = find_song(stoi(liked_songs_List[row][3]));
			find_user(liked_songs_List[row][0])->like(curr_song);
			curr_song->increase_number_of_likes();
		}
		else
		{
			users.push_back(new user(liked_songs_List[row][0],liked_songs_List[row][1],liked_songs_List[row][2]));
			song *curr_song = find_song(stoi(liked_songs_List[row][3]));
			find_user(liked_songs_List[row][0])->like(curr_song);
			curr_song->increase_number_of_likes();
		}
	}
}

UTunes::~UTunes()
{
	for(int i=0;i<users.size() ; i++)
		delete users[i];	
	for(int i=0;i<Filters.size() ;i++)
		delete Filters[i];
}

bool UTunes::user_already_exists(string username)
{
	for(int i=0 ; i<users.size() ;i++)
	{
		if(users[i]->get_username() == username)
			return true;
	}
	return false;
}


bool UTunes::compare_by_name(user *u1,user *u2)
{
	return u1->get_username() < u2->get_username();
}

void UTunes::add_artist_filter(string name)
{
	for(int i=0 ; i<Filters.size() ; i++)
	{
		if(Filters[i]->get_type() == ARTIST)
			Filters.erase(Filters.begin() +i);
	}
	Filters.push_back(new artist_filter(name));
}

vector<song*> UTunes::get_recommended_songs(string email)
{
	vector<song*> recommended_songs;
	current_user = find_user(email);
	recommendation recommend(&songs,&users);
	recommended_songs =recommend.get_recommended_songs(current_user , 4);
	return recommended_songs;
}

void UTunes::add_year_filter(int min_year,int max_year)
{
	
	for(int i=0 ; i<Filters.size() ; i++)
	{
		if(Filters[i]->get_type() == YEAR)
			Filters.erase(Filters.begin() +i);
	}
	Filters.push_back(new year_filter(min_year , max_year));
	
}

void UTunes::add_like_filter(int min_year , int max_year)
{

	for(int i=0 ; i<Filters.size() ; i++)
	{
		if(Filters[i]->get_type() == LIKE)
			Filters.erase(Filters.begin() +i);
	}
	Filters.push_back(new like_filter(min_year ,max_year));
}

void UTunes::remove_filters()
{	
		Filters.clear();		
}


playlist* UTunes::get_specific_playlist(int id)
{
	for(int i=0;i<users.size();i++)
	{
		if(users[i]->owns_playlist(id))
		{
			return users[i]->get_specific_playlist(id);
		}
	}
}

void UTunes::delete_song_from_playlist(string email,int playlist_id,int song_id)
{
	current_user = find_user(email);
	current_user->delete_song(playlist_id , song_id);
	find_song(song_id)->decrease_number_of_playlists();		
}

void UTunes::add_song_to_playlist(string email,int playlist_id,int song_id)
{
	current_user = find_user(email);
	song* song_to_add = find_song(song_id);
	current_user->add_song(playlist_id , song_to_add);
	song_to_add -> increase_number_of_playlists();
}

vector<playlist> UTunes::get_playlist(string email)
{
	current_user = find_user(email);
	vector<playlist> playlists=current_user->get_all_playlists();
	return playlists;
}

void UTunes::create_playlist(string email,string name,string privacy)
{
	current_user = find_user(email);
	current_user->add_playlist(name , privacy , next_playlist_id);
	next_playlist_id++;
}

void UTunes::delete_likes(int id , string email)
{
	current_user = find_user(email);
	current_user->delete_like(id);
	find_song(id)->decrease_number_of_likes();
}

song* UTunes::find_song(int id)
{
	for(int i=0;i<songs.size();i++)
	{
		if(songs[i].get_id() == id)
			return &songs[i];
	}
	throw Not_Found_Error();
}

user* UTunes::find_user(string email)
{
	for(int i=0;i<users.size();i++)
	{
		if(users[i]->get_email() == email)
			return users[i];
	}
}

void UTunes::post_like(int id,string email)
{
	current_user = find_user(email);
	song *curr_song = find_song(id);
	current_user->like(curr_song);
	curr_song->increase_number_of_likes();
}

vector<song*> UTunes::get_likes(string email)
{
	current_user = find_user(email);
	vector<song*> liked_songs=current_user->get_liked_songs();
	return liked_songs;
}

vector<song> UTunes::get_songs()
{
	vector<song> filtered_songs = songs;
	for(int i=0;i<Filters.size() ; i++)
		filtered_songs = Filters[i]->apply_filter(&filtered_songs);
	return filtered_songs;
}


void UTunes::signup(string email ,string username ,string pass)
{
	for(int i=0; i< users.size() ; i++)
	{
		if(users[i]->get_email() == email || users[i]->get_username() == username)
			throw Bad_Request_Error();
	}
	current_user = new user(email , username, pass);
	users.push_back(current_user);
}

void UTunes::login(string email,string pass)
{
	for(int i=0; i< users.size() ; i++)
	{
		if(users[i]->get_email() == email && users[i]->get_password() == pass)
		{
			return;
		}
	}
	throw Bad_Request_Error();
}