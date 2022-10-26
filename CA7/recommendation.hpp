#ifndef Recommendation_H
#define  Recommendation_H "Recommendation_H"

#include "user.hpp"
#include "song.hpp"
#include "matrix.hpp"
#include <string>
#include <sstream>
#include <vector>


class recommendation
{
public:
	recommendation(std::vector<song> *songs_ , std::vector<user*> *users_);
	void print_similar_users(user *current_user ,int count);
	std::vector<song*> get_recommended_songs(user *current_user ,int count);
private:
	void create_users_and_songs_matrix();
	void create_similarity_matrix();
	int number_of_common_songs_between(std::string user1 , std::string user2);
	user* find_user(std::string name);
	song* find_song(int id);
	matrix users_and_songs_matrix;
	matrix similarity_matrix;
	std::vector<song> *songs;
	std::vector<user*> *users;
};

#endif