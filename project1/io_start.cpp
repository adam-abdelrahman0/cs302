#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
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
    string line, currentString;
    int curTime;

    vector<Song> tempSongs;

    musicFile.open(argv[1]);

    while (musicFile) {
        Song currentSong;

        getline(musicFile, line);

        stringstream ss;

        ss << line;

        getline(ss, currentString, ' ');
        currentSong.title = currentString;

        getline(ss, currentString, ' ');
        currentSong.time = currentString;

        tempSongs.push_back(currentSong);
    }
    
    for (int i = 0; i < tempSongs.size(); i++) {
        cout << tempSongs.at(i).title << " " << tempSongs.at(i).time << endl;
    }
    musicFile.close();

    return 0;
}