#ifndef Playlist_H
#define  Playlist_H "Playlist_H"

#include "song.hpp"
#include <string>
#include <vector>


class playlist{
public:
	playlist(std::string name_,std::string privacy_ , int id);
	void print_data();
	void add(song* song_);
	//song* get_song(int id);
	void delete_Song(int song_id);
	bool get_privacy_situation();
	int get_id();
	std::string get_name();
	std::vector<song*> get_playlist_songs();
private:
	bool static compare( song *s1,song *s2);
	std::string name;
	bool privacy;
	int playlist_id;
	std::vector<song*> playlist_songs;
};

#endif