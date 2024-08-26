#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Plank-provided structs
struct Song { 
    string title;
    string time; // for total time in seconds
};

struct Album {
    map <string, Song > songs;
    string name;
    int time;
    int nsongs;
};

struct Artist {
    map <string, Album > albums;
    string name;
    int time;
    int nsongs;
};

int main(int argc, char* argv[]) {
    ifstream musicFile;
    string line, currentLineString, artistName, albumName, songName, trackNum;

    vector<Song> tempSongs;
    map<string, Artist> artists;

    musicFile.open(argv[1]);

    while (!musicFile.eof()) {
        Song currentSong;

        getline(musicFile, line);

        // get full line from file to split whitespace
        stringstream ss;
        ss << line;

        // song title
        getline(ss, songName, ' ');
        replace(songName.begin(), songName.end(), '_', ' ');
        currentSong.title = songName;

        // song duration (TODO: convert to total seconds)
        getline(ss, currentLineString, ' ');
        currentSong.time = currentLineString;

        // song artist (add song to album and album to artist)
        getline(ss, artistName, ' ');
        replace(artistName.begin(), artistName.end(), '_', ' ');

        artists[artistName].name = artistName;
        //artists[currentLineString].time += currentSong.time;
        artists[artistName].nsongs++;

        getline(ss, albumName, ' ');
        replace(albumName.begin(), albumName.end(), '_', ' ');
        artists[artistName].albums[albumName].name = albumName;
        //artists[currentLineString].albums[currentTempString].time = currentSong.time;
        artists[artistName].albums[albumName].nsongs++;

        getline(ss, currentLineString, ' ');
        getline(ss, currentLineString, ' ');
        trackNum = currentLineString;

        artists[artistName].albums[albumName].songs[trackNum].title = currentSong.title;
        artists[artistName].albums[albumName].songs[trackNum].time = currentSong.time;


        tempSongs.push_back(currentSong);
    }
    
    for (int i = 0; i < tempSongs.size(); i++) {
        cout << tempSongs.at(i).title << " " << tempSongs.at(i).time << endl;
    }

    cout << "\n\n---------- testing structs ----------\n\n" << endl;
    
    for (auto itr = artists.begin(); itr != artists.end(); ++itr) {
        cout << itr->first << ": " << itr->second.nsongs << ", " << endl;

        for (auto albumsItr = itr->second.albums.begin(); albumsItr != itr->second.albums.end(); ++albumsItr) {
            cout << "\t" << albumsItr->first << ": " << albumsItr->second.nsongs << endl;

            for (auto songsItr = albumsItr->second.songs.begin(); songsItr != albumsItr->second.songs.end(); ++songsItr) {
            cout << "\t \t" << songsItr->first << ": " << songsItr->second.title << endl;
        }
        }
    }
    musicFile.close();

    return 0;
}