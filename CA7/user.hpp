#ifndef User_H
#define  User_H "User_H"

#include "song.hpp"
#include <string>
#include <vector>
#include "playlist.hpp"


class user{
public:
	user(std::string Email ,  std::string Username , std::string Password );
	user();
	void like(song* song_to_like);
	std::vector<song*> get_liked_songs();
	void delete_like(int song_id);
	void add_playlist(std::string name , std::string privacy , int id);
	std::vector<playlist> get_all_playlists();
	void get_public_playlists();
	void add_song(int playlist_id , song* song_to_add);
	bool owns_playlist(int playlist_id);
	playlist* get_specific_playlist(int playlist_id);
	void delete_song(int playlist_id , int song_id);
	void get_public_playlists_songs(int playlist_id);
	bool has_liked_song(song *Song);
	std::vector<int> get_liked_songs_id();
	std::string get_email();
	std::string get_password();
	std::string get_username();
private:
	bool static compare(song *s1,song *s2);
	playlist* find_playlist(int id);
	std::vector<playlist> playlists;
	std::vector<song*> liked_songs;
	std::string email;
	std::string password;
	std::string username;

};

#endif