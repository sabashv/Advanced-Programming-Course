#include "recommendation.hpp"

#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

const string percentage_sign = "%";
const int floating_point_precision = 2;

recommendation::recommendation(vector<song> *songs_ , vector<user*> *users_)
{
	songs = songs_;
	users = users_;
	 create_users_and_songs_matrix();
	 create_similarity_matrix();
}


void recommendation::create_users_and_songs_matrix()
{
	vector<vector<double>> temp_vec(users->size() ,vector<double> (songs->size() , 0));
	vector<string> names , songs_id;
	for(int i=0 ;i<songs->size() ;i++)
		songs_id.push_back(to_string((*songs)[i].get_id()));
	for(int i=0 ;i<users->size() ;i++)
	{
		 for(int j=0 ; j<songs->size() ; j++)
		 {
			if((*users)[i]->has_liked_song(&(*songs)[j]))
		 		temp_vec[i][j] = 1;
		 	else
		 		temp_vec[i][j] = 0;
		}
		names.push_back((*users)[i]->get_username());
	}
	users_and_songs_matrix = matrix(songs_id  ,names ,temp_vec);
	
}

void recommendation::create_similarity_matrix()
{
	vector<vector<double>> temp_vec(users->size() ,vector<double> (users->size()));
	vector<string> names ;
	for(int i=0 ;i<users->size() ;i++)
	{
		for(int j=0;j<users->size() ;j++)
		{
			int number_of_common_songs = number_of_common_songs_between((*users)[i]->get_username() , (*users)[j]->get_username());
			if(number_of_common_songs == -1)
				temp_vec[i][j] = -1;
			else
				temp_vec[i][j] = double(number_of_common_songs)/double(songs->size());
		}
		names.push_back((*users)[i]->get_username());
	}
	similarity_matrix = matrix(names , names , temp_vec);
}

int recommendation::number_of_common_songs_between(string user1 , string user2)
{
	if(user1 == user2)
		return -1;
	int count=0;
	vector<int> songs_id1 , songs_id2;
	songs_id1 = find_user(user1)->get_liked_songs_id();
	songs_id2 = find_user(user2)->get_liked_songs_id();
	for(int i=0 ; i<songs_id1.size() ; i++)
	{
		for(int j=0 ; j<songs_id2.size() ;j++)
		{
			if(songs_id1[i] == songs_id2[j])
				count++;
		}
	}
	return count;
}

void recommendation::print_similar_users(user *current_user , int count)
{

	int row_number = similarity_matrix.find_row(current_user->get_username());
	similarity_matrix.sort_row(row_number);
	for(int i=0 ; i<count ;i++)
		cout<<fixed<<setprecision(floating_point_precision)<<similarity_matrix(row_number , i) *100<<percentage_sign<<" "<<similarity_matrix.get_name(i)<<endl;
}

vector<song*> recommendation::get_recommended_songs(user *current_user ,int count)
{
	create_users_and_songs_matrix();
	create_similarity_matrix();
	vector<song*> recommended_songs;
	matrix confidences = similarity_matrix * users_and_songs_matrix;
	int row_number = confidences.find_row(current_user->get_username());
	 confidences.sort_row(row_number);
	for(int i=0; i<count && i<songs->size(); i++)
	{
		song *Song = find_song(confidences.get_song_id(i));
		if(!current_user->has_liked_song(Song))
			recommended_songs.push_back(Song);
		else
			count++;
	}
	return recommended_songs;
}


user* recommendation::find_user(string name)
{
	for(int i=0;i<users->size();i++)
	{
		if((*users)[i]->get_username() == name)
			return (*users)[i];
	}
}

song* recommendation::find_song(int id)
{
	for(int i=0;i<songs->size();i++)
	{
		if((*songs)[i].get_id() == id)
			return &(*songs)[i];
	}
}