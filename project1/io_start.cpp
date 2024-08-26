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
    map <int, Song > songs;
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
    string line, currentLineString, currentTempString; 
    // use currentLineString for the section (one of six) of the current line parse (ex. song name vs. song duration, split by space)
    // use currentTempString for parsing within currentLineString (ex. song name, split by '_')
    int curTime;

    vector<Song> tempSongs;
    map<string, Artist> artists;

    musicFile.open(argv[1]);

    while (musicFile) {
        Song currentSong;

        getline(musicFile, line);

        // get full line from file to split whitespace
        stringstream ss;
        ss << line;

        // song title
        getline(ss, currentLineString, ' ');
        replace(currentLineString.begin(), currentLineString.end(), '_', ' ');
        currentSong.title = currentLineString;

        // song duration
        getline(ss, currentLineString, ' ');
        currentSong.time = currentLineString;

        // song artist (add song to album and album to artist)
        getline(ss, currentLineString, ' ');

        artists[currentLineString].name = currentLineString;
        //artists[currentLineString].time = currentSong.time;
        artists[currentLineString].nsongs++;

        getline(ss, currentTempString, ' ');
        artists[currentLineString].albums[currentTempString].name = currentTempString;
        //artists[currentLineString].albums[currentTempString].time = currentSong.time;
        artists[currentLineString].albums[currentTempString].nsongs++;

        //artists[currentLineString].albums[currentTempString].songs[currentSong.title].title = currentSong.title;
        //artists[currentLineString].albums[currentTempString].songs[currentSong.title].time = currentSong.time;


        tempSongs.push_back(currentSong);
    }
    
    for (int i = 0; i < tempSongs.size(); i++) {
        cout << tempSongs.at(i).title << " " << tempSongs.at(i).time << endl;
    }

    cout << "\n\n---------- testing structs ----------\n\n" << endl;
    
    for (auto itr = artists.begin(); itr != artists.end(); ++itr) {
        cout << '\t' << itr->first << '\t' << itr->second.name
             << '\n';
    }
    musicFile.close();

    return 0;
}