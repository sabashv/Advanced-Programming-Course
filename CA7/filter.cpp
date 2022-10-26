#include "filter.hpp"
#include "Exception.hpp"
#include <exception>
#include <algorithm>
#include <iostream>
using namespace std;

const string YEAR = "year";
const string LIKE = "like";
const string ARTIST = "artist";

like_filter::like_filter(int min , int max)
{
	min_likes = min;
	max_likes = max;
}
year_filter::year_filter(int min , int max)
{
	min_year = min;
	max_year = max;
}

string year_filter::get_type(){return YEAR;}

string like_filter::get_type(){return LIKE;}

string artist_filter::get_type(){return ARTIST;}

artist_filter::artist_filter(string artist)
{
	artist_name = artist;
}

vector<song> artist_filter::apply_filter(vector<song> *all_songs)
{
	vector<song> filtered_songs;
	for(int i=0 ; i<all_songs->size() ;i++)
	{
		if((*all_songs)[i].get_artist() == artist_name)
			filtered_songs.push_back((*all_songs)[i]);
	}
	return filtered_songs;
}

vector<song> year_filter::apply_filter(vector<song> *all_songs)
{
	if(max_year < min_year)
		throw Bad_Request_Error();
	vector<song> filtered_songs;
	for(int i=0 ;i<all_songs->size() ;i++)
	{
		if((*all_songs)[i].get_release_year() <= max_year && (*all_songs)[i].get_release_year() >= min_year)
			filtered_songs.push_back((*all_songs)[i]);
	}
	return filtered_songs;
}

vector<song> like_filter::apply_filter(vector<song> *all_songs)
{
	if(max_likes < min_likes)
		throw Bad_Request_Error();
	vector<song> filtered_songs;
	for(int i=0 ; i<all_songs->size() ;i++)
	{
		if((*all_songs)[i].get_num_of_likes() <= max_likes && (*all_songs)[i].get_num_of_likes() >= min_likes)
			filtered_songs.push_back((*all_songs)[i]);
	}
	return filtered_songs;
}