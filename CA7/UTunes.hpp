#ifndef UTUnes_H
#define  UTUnes_H "UTUnes_H"

#include "user.hpp"
#include "song.hpp"
#include "filter.hpp"

class UTunes{
public:
	UTunes(std::string songs_file_address , std::string liked_songs_info);
	~UTunes();
	void signup(std::string email ,std::string username ,std::string pass);
	void login(std::string email , std::string pass);
	std::vector<song> get_songs();
	void post_like(int id,std::string email);
	std::vector<song*> get_likes(std::string email);
	void delete_likes(int id,std::string email);
	void create_playlist(std::string email,std::string name,std::string privacy);
	std::vector<playlist> get_playlist(std::string email);
	void add_song_to_playlist(std::string email,int playlist_id , int song_id);
	playlist* get_specific_playlist(int id);
	void delete_song_from_playlist(std::string email,int playlist_id , int song_id);
	void add_artist_filter(std::string input);
	void add_year_filter(int min , int max);
	void add_like_filter(int min , int max);
	void remove_filters();
	std::vector<song*> get_recommended_songs(std::string email);
	song* find_song(int id);
private:
	std::vector<filter*> Filters;
	bool user_already_exists(std::string username);
	void extract_songs_info(std::string file_address);
	void extract_liked_songs_info(std::string file_address);
	bool static compare_by_name(user *u1,user *u2);
	user* find_user(std::string name);
	int next_playlist_id;
	user *current_user;
	std::vector<song> songs;
	std::vector<user*> users;
};

#endif