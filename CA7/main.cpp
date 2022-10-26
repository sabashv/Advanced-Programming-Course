#include "handlers.hpp"
#include "my_server.hpp"
#include "Exception.hpp"
#include "UTunes.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

  UTunes utunes(argv[1] , "liked_songs.csv");
  try { 

    MyServer server( 5000);
    server.setNotFoundErrPage("static/404.html");
    
    server.get("/signup", new ShowPage("static/signupcss.html"));
    server.post("/signup", new SignupHandler(&utunes));
    server.get("/login", new ShowPage("static/logincss.html"));
    server.get("/loginerror", new ShowPage("static/loginerror.html"));
    server.get("/signuperror", new ShowPage("static/signuperror.html"));
    server.post("/login", new LoginHandler(&utunes));
    server.get("/logout",  new ShowPage("static/enter_page.html"));

    server.get("/home", new HomePage(&utunes));
    server.get("/HomePage.css", new ShowPage("static/HomePage.css"));

    server.get("/Artistfilter", new ArtistFilterHandler(&utunes));
    server.get("/Yearfilter", new YearFilterHandler(&utunes));
    server.get("/Likefilter", new LikeFilterHandler(&utunes));
    server.get("/Removefilter", new RemoveFilterHandler(&utunes));

    server.get("/filtererror", new ShowPage("static/filtererror.html"));

    server.get("/Not_Found_Error", new ShowPage("static/notfounderror.html"));

    server.get("/likeererror", new ShowPage("static/likeerror.html"));
    server.get("/deletelikeererror", new ShowPage("static/deletelikeerror.html"));

    server.get("/song_page", new SongPage(&utunes));
    server.get("/SongPage.css", new ShowPage("static/SongPage.css"));

    server.get("/like", new Like(&utunes));
    server.get("/dislike", new Dislike(&utunes));

    server.get("/liked_songs_page", new LikedSongs(&utunes));

    server.get("/deletelike", new DeleteLike(&utunes));
    server.get("/playlists_page", new Playlists(&utunes));
    server.get("/playlist_page", new Playlist(&utunes));
    server.get("/add_playlist", new AddPlaylist(&utunes));
    server.get("/add_song", new AddSong(&utunes));
    server.get("/delete_song_from_playlist", new DeleteSong(&utunes));
   
  
    server.get("/xxxx.jpg", new ShowPage("static/xxxx.jpg"));
    server.get("/index.jpeg", new ShowPage("static/c.png"));
  
    server.get("/", new ShowPage("static/enter_page.html"));
  
   server.run();
 }
 catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
 }
}

  
