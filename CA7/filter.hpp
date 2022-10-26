#ifndef Filter_H
#define  Filter_H "Filter_H"

#include "song.hpp"
#include <string>
#include <vector>

class filter{
public:
	virtual std::vector<song> apply_filter(std::vector<song>* all_songs)=0;
	virtual std::string get_type() = 0;
};

class artist_filter : public filter{
public:
	artist_filter(std::string artist);
	std::vector<song> apply_filter(std::vector<song> *all_songs);
	std::string get_type();
private:
	std::string artist_name;
};

class year_filter : public filter{
public:
	year_filter(int min , int max);
	std::vector<song> apply_filter(std::vector<song>* all_songs);
	std::string get_type();
private:
	int min_year;
	int max_year;
};

class like_filter : public filter{
public:
	like_filter(int min , int max);
	std::vector<song> apply_filter(std::vector<song>* all_songs);
	std::string get_type();
private:
	int min_likes;
	int max_likes;
};

#endif