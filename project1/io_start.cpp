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

    musicFile.open(argv[1]);

    while (musicFile) {
        Song currentSong;

        getline(musicFile, line);

        // get full line from file to split whitespace
        stringstream ss;
        ss << line;

        getline(ss, currentLineString, ' ');
        replace(currentLineString.begin(), currentLineString.end(), '_', ' ');
        currentSong.title = currentLineString;

        getline(ss, currentLineString, ' ');
        currentSong.time = currentLineString;

        tempSongs.push_back(currentSong);
    }
    
    for (int i = 0; i < tempSongs.size(); i++) {
        cout << tempSongs.at(i).title << " " << tempSongs.at(i).time << endl;
    }
    musicFile.close();

    return 0;
}