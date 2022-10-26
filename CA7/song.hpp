#ifndef Song_H
#define  Song_H "Song_H"



#include <string>
#include <vector>

class song{
public:
	song(std::string id_ , std::string title_ , std::string artist_ , std::string year_ , std::string link_);
	void increase_number_of_likes();
	void increase_number_of_playlists();
	void decrease_number_of_likes();
	void decrease_number_of_playlists();
	int get_id();
	std::string get_artist();
	std::string get_title();
	int get_release_year();
	int get_num_of_likes();
	int get_num_of_playlists();
	std::string get_link();
private:
	int num_of_likes;
	int num_of_playlists;
	int id;
	std::string title;
	std::string artist;
	int release_year;
	std::string link;
};

#endif