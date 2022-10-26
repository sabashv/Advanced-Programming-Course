#include "handlers.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;


LoginHandler::LoginHandler(UTunes *tunes):UTUNES(tunes){}

Response *LoginHandler::callback(Request *req) {
  string email = req->getBodyParam("email");
  string password = req->getBodyParam("password");
  Response *res = new Response;
  try
  {
    UTUNES->login(email,password);
    UTUNES->remove_filters();
    res->setHeader("Content-Type", "text/html");
    res = Response::redirect("/home");
    res->setSessionId(email);
  }
  catch (Bad_Request_Error &e) 
  {
    res = Response::redirect("/loginerror");
  }
  return res;
}

SignupHandler::SignupHandler(UTunes *tunes):UTUNES(tunes){}

Response *SignupHandler::callback(Request *req) {
  Response *res;
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  string email = req->getBodyParam("email");
  try
  {
    UTUNES->signup(email ,username,password);
    res = Response::redirect("/");
  }
  catch (Bad_Request_Error &e) 
  {
    res = Response::redirect("/signuperror");
  }
  return res;
}

string HomePage::create_song_table()
{
  vector<song> songs = UTUNES->get_songs(); 
  ostringstream body;
  if(songs.size() == 0)
  {
    body
     <<"<p>List is empty</p>"<<endl;
     return body.str();
  }
  body
  <<"<table id='table'>"<<endl
  <<"<tr>"<<endl
  <<"<th>ID</th>"<<endl
  <<"<th>Title</th>"<<endl
  <<"<th>Artist</th>"<<endl
  <<"<th>Release_year</th>"<<endl
  <<"</tr>"<<endl;
  for(unsigned int i=0; i<songs.size() ;i++)
  {
    body
    <<"<tr>"<<endl
    <<"<td>"<<songs[i].get_id()<<"</td>"<<endl
    <<"<td><a href='song_page?id="<<songs[i].get_id()<<"'> "<<songs[i].get_title()<<"</a>" << "</td>"<<endl
    <<"<td>"<<songs[i].get_artist()<<"</td>"<<endl
    <<"<td>"<<songs[i].get_release_year()<<"</td>"<<endl
    <<"</tr>"<<endl;
  }
  body
  <<"</table>"<<endl;
  return body.str();
}

string HomePage::create_artist_filter_form()
{
   ostringstream body;
   body
    <<" <form action=\"/Artistfilter\">"<<endl
    <<"<label for=\"artist_name\">Artist Name</label>"<<endl
    <<" <input type=\"text\" id=\"artist_name\" name=\"artist_name\" placeholder=\"Artist name..\">"<<endl
    <<"<input type=\"submit\" value=\"Submit\">"<<endl
    <<"</form>"<<endl;
    return body.str();

}

string HomePage::create_year_filter_form()
{
  ostringstream body;
   body
    <<"<form action=\"/Yearfilter\">"<<endl
    <<"<label for=\"Year\">Release Year</label>"<<endl
    <<"<input type=\"text\" id=\"min_year\" name=\"min_year\" placeholder=\"min_year..\">"<<endl
    <<"<input type=\"text\" id=\"max_year\" name=\"max_year\" placeholder=\"max_year..\">"<<endl
    <<"<input type=\"submit\" value=\"Submit\">"<<endl
    <<"</form>"<<endl;
    return body.str();
}

string HomePage::create_like_filter_form()
{
   ostringstream body;
   body
   <<" <form action=\"/Likefilter\">"<<endl
    <<"<label for=\"Like\">Likes </label>"<<endl
    <<" <input type=\"text\" id=\"min_like\" name=\"min_like\" placeholder=\"min_like..\">"<<endl
    <<" <input type=\"text\" id=\"max_like\" name=\"max_like\" placeholder=\"max_like..\">"<<endl
    <<"<input type=\"submit\" value=\"Submit\">"<<endl
    <<"</form>"<<endl;
    return body.str();
}

string HomePage::create_navbar()
{
   ostringstream body;
   body
    <<"<div class=\"topnav\">"<<endl
    <<"<a href=\"/liked_songs_page\">Liked Songs</a>"<<endl
    <<"<a href=\"/playlists_page\">Playlists</a>"<<endl
    <<"<a href=\"/logout\">Logout</a> "<<endl
    <<"</div>"<<endl;
    return body.str();
}

HomePage::HomePage(UTunes *tunes):UTUNES(tunes){}

Response *HomePage::callback(Request *req) {
  Response *res = new Response;
  try
  {
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body
    <<"<!DOCTYPE html>"<<endl
    <<"<html>"<<endl
    <<"<head>"<<endl
    <<"<title>Home</title>"<<endl
    <<"<link href=\"./HomePage.css\" type=\"text/css\" rel=\"stylesheet\"/>"<<endl
    <<"</head>"<<endl
    <<"<div class=\"header\">"<<endl
    <<"<h2>UTunes</h2>"
    <<"</div>"<<endl
    <<create_navbar()
    <<"<body>"<<endl
    <<"<div class=\"row\">"<<endl
    <<"<div class=\"column side\">"<<endl
    <<"<h2>Filters</h2>"<<endl
    <<create_artist_filter_form()
    <<create_year_filter_form()
    <<create_like_filter_form()
    <<"<a href=\"/Removefilter\" class='button'>Remove Filters</a>"<<endl
    <<"</div>"<<endl
    <<"<div class=\"column middle\">"<<endl
    <<create_song_table()
    <<"</div>"<<endl
    <<"</div>"<<endl
    <<"</body>"<<endl
    <<"</html>"<<endl;
    res->setBody(body.str());
  }
  catch (Bad_Request_Error &e) 
  {
    res = Response::redirect("/filtererror");
  }
  return res;
}

ArtistFilterHandler::ArtistFilterHandler(UTunes *tunes):UTUNES(tunes){}

Response *ArtistFilterHandler::callback(Request *req) {
  Response *res = new Response;
  string name = req->getQueryParam("artist_name");
  try
  {
    UTUNES->add_artist_filter(name);
    res = Response::redirect("/home");
  }
  catch (Bad_Request_Error &e) 
  {
    res = Response::redirect("/filtererror");
  }
  return res;
}

RemoveFilterHandler::RemoveFilterHandler(UTunes *tunes):UTUNES(tunes){}

Response *RemoveFilterHandler::callback(Request *req) {
  UTUNES->remove_filters();
  return Response::redirect("/home");
}

YearFilterHandler::YearFilterHandler(UTunes *tunes):UTUNES(tunes){}

Response *YearFilterHandler::callback(Request *req) {
  Response *res = new Response;
  string min_year = req->getQueryParam("min_year");
  string max_year = req->getQueryParam("max_year");
  try
  {
    UTUNES->add_year_filter(stoi(min_year) , stoi(max_year));
    res = Response::redirect("/home");
  }
  catch (Bad_Request_Error &e) 
  {
    res = Response::redirect("/filtererror");
  }
  return res;
}

LikeFilterHandler::LikeFilterHandler(UTunes *tunes):UTUNES(tunes){}

Response *LikeFilterHandler::callback(Request *req) {
  Response *res = new Response;
  string min_like = req->getQueryParam("min_like");
  string max_like = req->getQueryParam("max_like");
  try
  {
    UTUNES->add_like_filter(stoi(min_like) , stoi(max_like));
    res = Response::redirect("/home");
  }
  catch (Bad_Request_Error &e) 
  {
    res = Response::redirect("/filtererror");
  }
  return res;
}

Like::Like(UTunes *tunes):UTUNES(tunes){}

Response *Like::callback(Request *req) {
  Response *res = new Response;
  int id = stoi(req->getQueryParam("id"));
  string email = req->getSessionId();
  try
  {
    res->setHeader("Content-Type", "text/html");
    UTUNES->post_like(id ,email);
    string body;
    body="/song_page?id="+to_string(id);
    res = Response::redirect(body);
  }
  catch (Bad_Request_Error &e) 
  {
    res = Response::redirect("/likeererror");
  }
  catch(Not_Found_Error &error)
  {
   res = Response::redirect("/likeererror");
  }

  return res;
}

string LikedSongs::create_table(string email)
{
  vector<song*> songs = UTUNES->get_likes(email);
  ostringstream body;
  if(songs.size()==0)
  {
    body
    <<"<p>List is empty</p>"<<endl;
    return body.str();
  }
  body
  <<"         <table id='table'>"<<endl
  <<"         <tr>"<<endl
  <<"           <th>ID</th>"<<endl
  <<"           <th>Title</th>"<<endl
  <<"          <th>Artist</th>"<<endl
  <<"           <th>Release_year</th>"<<endl
  <<"           <th>&nbsp;</th>"<<endl
  <<"         </tr>"<<endl;

  for(unsigned int i=0; i<songs.size() ;i++)
  {
    body
      <<"                <tr>"<<endl
      <<"                     <td>"<<songs[i]->get_id()<<"</td>"<<endl
      <<"                     <td><a href='song_page?id="<<songs[i]->get_id()<<"'> "<<songs[i]->get_title()<<"</a>" << "</td>"<<endl
      <<"                     <td>"<<songs[i]->get_artist()<<"</td>"<<endl
      <<"                     <td>"<<songs[i]->get_release_year()<<"</td>"<<endl
      <<"                     <td><a href='deletelike?id="<<songs[i]->get_id()<<"'class='Secondbutton' >Delete Like</a>" << "</td>"<<endl
      <<"                </tr>"<<endl;
  }
  body
  << "</table>"<<endl;
  return body.str();
}

LikedSongs::LikedSongs(UTunes *tunes):UTUNES(tunes){}

Response *LikedSongs::callback(Request *req) {
  Response *res = new Response;
  string email = req->getSessionId();
  res->setHeader("Content-Type", "text/html");
  ostringstream body;
     body
     <<"<!DOCTYPE html>"<<endl
     <<"<html>"<<endl
     <<"<head>"<<endl
     <<"<title>Liked Songs</title>"<<endl
     <<"<link href=\"./HomePage.css\" type=\"text/css\" rel=\"stylesheet\"/>"<<endl
     <<"</head>"<<endl
     <<"<div class=\"header\">"<<endl
     <<"<h2>Utunes</h2>"
     <<"</div>"<<endl
     <<"<div class=\"topnav\">"<<endl
     <<"<a href=\"/logout\">Logout</a> "<<endl
     <<"</div>"<<endl
     <<"<body>"<<endl
     <<"<div class=\"row\">"<<endl
     <<"<div class=\"column middle\">"<<endl
     <<create_table(email)
     <<"</div>"<<endl
     <<"</div>"<<endl
     <<"</body>"<<endl
     <<"</html>"<<endl;
     res->setBody(body.str());
  return res;
}

string Playlists::create_table(string email)
{
   vector<playlist> playlists = UTUNES->get_playlist(email);
   ostringstream body;
   if(playlists.size()==0)
   {
    body
     <<"<p>List is empty.</p>"<<endl;
    return body.str();
   }
   body
   <<"         <table id='table'>"<<endl
   <<"         <tr>"<<endl
   <<"           <th>Name</th>"<<endl
   <<"          <th>Public/Private</th>"<<endl
   <<"         </tr>"<<endl;
   for(unsigned int i=0; i<playlists.size() ;i++)
   {
    body
      <<"                <tr>"<<endl
      <<"                     <td><a href='playlist_page?id="<<playlists[i].get_id()<<"'> "<<playlists[i].get_name()<<"</a>" << "</td>"<<endl;
      if(playlists[i].get_privacy_situation())
      {
        body
          <<"                     <td>Public</td>"<<endl;
      }
      else
      {
        body
          <<"                     <td>Private</td>"<<endl;
      }
      body
      <<"                </tr>"<<endl;
   }
  body
  <<                  "</table>"<<endl;
  return body.str();
}

string Playlists::create_playlist_form()
{
  ostringstream body;
  body
  <<"<h2>Add Playlist</h2>"<<endl
  <<"<form action=\"/add_playlist\">"<<endl
  <<"<input type=\"text\" id=\"playlist_name\" name=\"playlist_name\" placeholder=\"Playlist name..\">"<<endl
  <<"<label for=\"privacy\">Public/Private</label>"<<endl
  <<"<select id = \"privacy\" name=\"privacy\">"<<endl
  <<"<option value ='1'>Public</option>"<<endl
  <<"<option value ='0'>Private</option>"<<endl
  <<"</select>"<<endl
  <<"<input type=\"submit\" value=\"Add\">"<<endl
  <<"</form>"<<endl;
  return body.str();
}
Playlists::Playlists(UTunes *tunes):UTUNES(tunes){}

Response *Playlists::callback(Request *req) {
  Response *res = new Response;
  string email = req->getSessionId();
  res->setHeader("Content-Type", "text/html");
  ostringstream body;
  body
  <<"<!DOCTYPE html>"<<endl
  <<"<html>"<<endl
  <<"<head>"<<endl
   <<"<title>Playlists</title>"<<endl
  <<"<link href=\"./HomePage.css\" type=\"text/css\" rel=\"stylesheet\"/>"<<endl
  <<"</head>"<<endl
  <<"<div class=\"header\">"<<endl
  <<"<h2>UTutnes</h2>"
  <<"</div>"<<endl
  <<"<div class=\"topnav\">"<<endl
  <<"<a href=\"/logout\">Logout</a> "<<endl
  <<"</div>"<<endl
  <<"<div class=\"row\">"<<endl
  <<"<div class=\"column side\">"<<endl
  <<create_playlist_form()
  <<"</div>"<<endl
  <<"<body>"<<endl
  <<"<div class=\"column middle\">"<<endl
  <<create_table(email)
  <<"</div>"<<endl
  <<"</div>"<<endl
  <<"</body>"<<endl
  <<"</html>"<<endl;
  res->setBody(body.str());
  return res;
}

string Playlist::create_song_table(playlist *Playlist , string id)
{
  vector<song*> songs = Playlist->get_playlist_songs();
  ostringstream body;
  if(songs.size()==0)
  {
    body
    <<"<p>List is empty.</p>"<<endl;
    return body.str();
  }
  body
  <<"         <table id='table'>"<<endl
  <<"         <tr>"<<endl
  <<"           <th>ID</th>"<<endl
  <<"           <th>Title</th>"<<endl
  <<"          <th>Artist</th>"<<endl
  <<"           <th>Release year</th>"<<endl
  <<"           <th>Delete song</th>"<<endl
  <<"         </tr>"<<endl;
  for(unsigned int i=0; i<songs.size() ;i++)
  {
    body
      <<"                <tr>"<<endl
      <<"                     <td>"<<songs[i]->get_id()<<"</td>"<<endl
      <<"                     <td><a href='song_page?id="<<songs[i]->get_id()<<"'> "<<songs[i]->get_title()<<"</a>" << "</td>"<<endl
      <<"                     <td>"<<songs[i]->get_artist()<<"</td>"<<endl
      <<"                     <td>"<<songs[i]->get_release_year()<<"</td>"<<endl
      <<"                     <td><a href='delete_song_from_playlist?Sid="<<songs[i]->get_id()<<"&Pid="<<id<<"'class='Secondbutton' >Delete</a>" << "</td>"<<endl
      <<"                </tr>"<<endl;
  }
  body
  <<                  "</table>"<<endl;
  return body.str();
}

string Playlist::create_add_song_form(string id)
{
  ostringstream body;
  body
  <<"<h3>Add Song</h3>"<<endl
  <<"<form action=\"/add_song\">"<<endl
  <<"<input type=\"hidden\" id=\"playlist_id\" name=\"playlist_id\" value="<<id<<">"<<endl
  <<"<input type=\"text\" name=\"song_id\" placeholder=\"Song ID..\">"<<endl
  <<"<input type=\"submit\" value=\"Add\">"<<endl
  <<"</form>"<<endl;
  return body.str();
}
Playlist::Playlist(UTunes *tunes):UTUNES(tunes){}

Response *Playlist::callback(Request *req) {
  Response *res = new Response;
  string id = req->getQueryParam("id");
 playlist *Playlist = UTUNES->get_specific_playlist(stoi(id));
 
  res->setHeader("Content-Type" ,"text/html");
  ostringstream body;
  body
  <<"<!DOCTYPE html>"<<endl
  <<"<html>"<<endl
  <<"<head>"<<endl
  <<"<title>Playlist Page</title>"<<endl
  <<"<link href=\"./HomePage.css\" type=\"text/css\" rel=\"stylesheet\"/>"<<endl
  <<"</head>"<<endl
  <<"<div class=\"header\">"<<endl
  <<"<h1>UTunes.</h1>"
  <<"</div>"<<endl
  <<"<div class=\"topnav\">"<<endl
  <<"<a href=\"/logout\">Logout</a> "<<endl
  <<"</div>"<<endl
  <<"<div class=\"row\">"<<endl
  <<"<div class=\"column side\">"<<endl
  <<create_add_song_form(id)
  <<"</div>"<<endl
  <<"<body>"<<endl
  <<"<div class=\"column middle\">"<<endl
  <<"<h2>Playlist</h2>"<<endl
  <<"<ul>"<<endl
  <<"<li>Playlist name : "<<Playlist->get_name()<<"</li>"<<endl;
  if(Playlist->get_privacy_situation())
  {
    body
    <<"<li>"<<"Public/Private : Public</li>"<<endl;
  }
  else
  {
    body
    <<"<li>"<<"Public/Private : Private</li>"<<endl;
  }
  body
  <<"<li>Songs list : ""</li>"<<endl
  <<"<body>"<<endl
  <<"<div class=\"row\">"<<endl
  <<"<div class=\"column middle\">"<<endl
  <<create_song_table(Playlist,id)
  <<"</div>"<<endl
  <<"</div>"<<endl
  <<"</body>"<<endl
  <<"</html>"<<endl;
  res->setBody(body.str());
  return res;
}


AddPlaylist::AddPlaylist(UTunes *tunes):UTUNES(tunes){}

Response *AddPlaylist::callback(Request *req) {
  Response *res = new Response;
  string playlist_name = req->getQueryParam("playlist_name");
  string privacy = req->getQueryParam("privacy");
  string email = req->getSessionId();
  try
  {
    res->setHeader("Content-Type", "text/html");
    UTUNES->create_playlist(email ,playlist_name,privacy);
    string body;
    body="/playlists_page";
    res = Response::redirect(body);
  }
  catch (Bad_Request_Error &e) 
  {
    res = Response::redirect("/likeererror");
  }
  return res;
}

DeleteSong::DeleteSong(UTunes *tunes):UTUNES(tunes){}

Response *DeleteSong::callback(Request *req) {
  Response *res = new Response;
 string playlist_id = req->getQueryParam("Pid");
  string song_id = req->getQueryParam("Sid");
  string email = req->getSessionId();
  try
  {
    res->setHeader("Content-Type", "text/html");
    UTUNES->delete_song_from_playlist(email ,stoi(playlist_id),stoi(song_id));
    string body;
     body="/playlist_page?id=1";
    res = Response::redirect(body);
  }
  catch (Bad_Request_Error &e) 
  {
    res = Response::redirect("/likeererror");
  }
  return res;
}

AddSong::AddSong(UTunes *tunes):UTUNES(tunes){}

Response *AddSong::callback(Request *req) {
  Response *res = new Response;
  int song_id = stoi(req->getQueryParam("song_id"));
  int playlist_id = stoi(req->getQueryParam("playlist_id"));
  string email = req->getSessionId();
  try
  {
    res->setHeader("Content-Type", "text/html");
    UTUNES->add_song_to_playlist(email,playlist_id,song_id);
    string body = "/playlist_page?id="+to_string(playlist_id);
    res = Response::redirect(body);
  }
  catch (Not_Found_Error &e) 
  {
    res = Response::redirect("/Not_Found_Error");
  }
  return res;
}

Dislike::Dislike(UTunes *tunes):UTUNES(tunes){}

Response *Dislike::callback(Request *req) {
  Response *res = new Response;
  int id = stoi(req->getQueryParam("id"));
  string email = req->getSessionId();
  try
  {
    res->setHeader("Content-Type", "text/html");
    UTUNES->delete_likes(id ,email);
    string body="/song_page?id="+to_string(id);
    res = Response::redirect(body);
  }
  catch (Bad_Request_Error &e) 
  {
    res = Response::redirect("/deletelikeererror");
  }
  return res;
}

DeleteLike::DeleteLike(UTunes *tunes):UTUNES(tunes){}

Response *DeleteLike::callback(Request *req) {
  Response *res = new Response;
  int id = stoi(req->getQueryParam("id"));
  string email = req->getSessionId();
  try
  {
    res->setHeader("Content-Type", "text/html");
    UTUNES->delete_likes(id ,email);
    string body;
    body="/liked_songs_page";
    res = Response::redirect(body);
  }
  catch (Bad_Request_Error &e) 
  {
    res = Response::redirect("/likeererror");
  }
  return res;
}

string SongPage::recommended_songs(string email)
{
  vector<song*> recommended_songs = UTUNES->get_recommended_songs(email);
  ostringstream body;
  if(recommended_songs.size() == 0)
  {
    body
    <<"<p>List is empty</p>"<<endl;
    return body.str();
  }
  for(unsigned int i=0 ;i<recommended_songs.size();i++)
  {
    body
    <<"<div class='content'>"<<endl
    <<"        <ul>"<<endl
    <<"          <li>"<<"Title : "<<recommended_songs[i]->get_title()<<"</li>"<<endl
    <<"          <li>"<<"Release year : "<<recommended_songs[i]->get_release_year()<<"</li>"<<endl
    <<"          <li>"<<"Artist : "<<recommended_songs[i]->get_artist()<<"</li>"<<endl
    <<"        <br><br><ul/>"<<endl
    <<"</div>"<<endl;
  }
  return body.str();
}

string SongPage::create_navbar(int id)
{
  ostringstream body;
  body
  <<"<a href=\"/like?id="<<id<<"\" class='button'>Like</a>"<<endl
  <<"<a href=\"/dislike?id="<<id<<"\" class='button'>Dislike</a>"<<endl
  <<"<a href=\"/logout\" class='button'>Logout</a>"<<endl;
  return body.str();
}

string SongPage::print_song_info(int id)
{
  song *Song = UTUNES->find_song(id);
  ostringstream body;
  body
  <<"<h2>"<<Song->get_title()<<"</h2>"<<endl
  <<"<ul>"<<endl
  <<"<li>"<<"Artist : "<<Song->get_artist()<<"</li>"<<endl
  <<"<li>"<<"Release year : "<<Song->get_release_year()<<"</li>"<<endl
  <<"<li>"<<"Likes : "<<Song->get_num_of_likes()<<"</li>"<<endl
  <<"<li>"<<"Number of playlists : "<<Song->get_num_of_playlists()<<"</li>"<<endl
  <<"<ul/>"
  <<"</div>"<<endl
  <<"<div class='content'>"<<endl
  <<"<audio controls>"<<endl
  <<"<br><source src="<<Song->get_link()<<" type=\"audio/mpeg\" >"<<endl
  <<"</audio>"<<endl;
  return body.str();
}

SongPage::SongPage(UTunes *tunes):UTUNES(tunes){}

Response *SongPage::callback(Request *req) {
  Response *res = new Response;
  int id = stoi(req->getQueryParam("id"));

  res->setHeader("Content-Type" ,"text/html");
  ostringstream body;
  body
  <<"<!DOCTYPE html>"<<endl
  <<"<html>"<<endl
  <<"<head>"<<endl
  <<"<title>Song Page</title>"<<endl
  <<"<link href=\"/SongPage.css\" type=\"text/css\" rel=\"stylesheet\"/>"<<endl
  <<"</head>"<<endl
  <<"<body>"<<endl
  <<"<div class='sidenav'>"<<endl
  <<create_navbar(id)
  <<"</div>"<<endl
  <<"<div class='content'>"<<endl
  <<print_song_info(id)
  <<"</div>"<<endl
  << "<div class='content'>"<<endl
  <<"<br><h3>Recommended songs</h3>"<<endl
  <<"</div>"<<endl
  <<recommended_songs(req->getSessionId())
  <<"</body>"<<endl
  <<"</html>"<<endl;
  res->setBody(body.str());
  return res;
}


Response *ExceptionHandler::callback(Request *req) {
  
  Response *res = Response::redirect("/");
  return res;
}