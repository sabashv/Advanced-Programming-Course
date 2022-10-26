#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include "Exception.hpp"
#include "UTunes.hpp"
#include <iostream>


class LoginHandler : public RequestHandler {
public:
   LoginHandler(UTunes * tunes);
  Response *callback(Request *);

private:
	UTunes *UTUNES;
};

class ArtistFilterHandler : public RequestHandler {
public:
 ArtistFilterHandler(UTunes * tunes);
  Response *callback(Request *);
private:
  UTunes *UTUNES;
};

class YearFilterHandler : public RequestHandler {
public:
 YearFilterHandler(UTunes * tunes);
  Response *callback(Request *);
private:
  UTunes *UTUNES;
};

class RemoveFilterHandler : public RequestHandler {
public:
 RemoveFilterHandler(UTunes * tunes);
  Response *callback(Request *);
private:
  UTunes *UTUNES;
};

class LikeFilterHandler : public RequestHandler {
public:
 LikeFilterHandler(UTunes * tunes);
  Response *callback(Request *);
private:
  UTunes *UTUNES;
};

class HomePage : public RequestHandler {
public:
  HomePage(UTunes * tunes);
  Response *callback(Request *);
private:
  std::string create_song_table();
  std::string create_artist_filter_form();
  std::string create_year_filter_form();
  std::string create_like_filter_form();
  std::string create_navbar();
  UTunes *UTUNES;
};

class SongPage : public RequestHandler {
public:
   SongPage(UTunes * tunes);
   Response *callback(Request *);

private:
  std::string create_navbar(int id);
  std::string recommended_songs(std::string email);
  std::string print_song_info(int id);
	UTunes *UTUNES;
};


class Like : public RequestHandler {
public:
   Like(UTunes * tunes);
   Response *callback(Request *);

private:
  UTunes *UTUNES;
};

class DeleteSong : public RequestHandler {
public:
   DeleteSong(UTunes * tunes);
   Response *callback(Request *);

private:
  UTunes *UTUNES;
}; 

class LikedSongs : public RequestHandler {
public:
   LikedSongs(UTunes * tunes);
   Response *callback(Request *);

private:
  std::string create_table(std::string email);
  UTunes *UTUNES;
};

class Dislike : public RequestHandler {
public:
   Dislike(UTunes * tunes);
   Response *callback(Request *);

private:
  UTunes *UTUNES;
};

class DeleteLike : public RequestHandler {
public:
   DeleteLike(UTunes * tunes);
   Response *callback(Request *);

private:
  UTunes *UTUNES;
};

class Playlists : public RequestHandler {
public:
   Playlists(UTunes * tunes);
   Response *callback(Request *);

private:
  std::string create_playlist_form();
  std::string create_table(std::string email);
  UTunes *UTUNES;
};

class AddPlaylist : public RequestHandler {
public:
   AddPlaylist(UTunes * tunes);
   Response *callback(Request *);

private:
  UTunes *UTUNES;
};

class AddSong : public RequestHandler {
public:
   AddSong(UTunes * tunes);
   Response *callback(Request *);

private:
  UTunes *UTUNES;
};

class Playlist : public RequestHandler {
public:
   Playlist(UTunes * tunes);
   Response *callback(Request *);
private:
  std::string create_add_song_form(std::string id);
  std::string create_song_table(playlist *Playlist,std::string id);
  UTunes *UTUNES;
};


class ExceptionHandler : public RequestHandler {
public:
  ExceptionHandler();
  Response *callback(Request *);
private:
};

class SignupHandler : public RequestHandler {
public:
  SignupHandler(UTunes * tunes);
  Response *callback(Request *);
private:
	UTunes *UTUNES;
};



#endif
