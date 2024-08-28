#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
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

string str_time(int seconds) {
	string time_out, hh, mm, ss;
	int hours = 0;
	int minutes = 0;

	//hours = seconds / 3600;
	//seconds -= hours * 3600;
	minutes = seconds / 60;
	seconds -= minutes * 60;

	hh = to_string(hours);
	mm = to_string(minutes);
	ss = to_string(seconds);

	stringstream time_stream;

	if (hours > 0) {
		time_stream << setfill('0') << setw(2) << hh << ":";
	}
	if (minutes > 0 && hours == 0) {
		time_stream  << mm << ":";
	}
		else if (minutes > 0 && hours > 0) {
			time_stream << setfill('0') << setw(2) << hh << ":";
		}
	if (seconds > 0 && minutes == 0 && hours == 0) {
		time_stream << "0:" << setfill('0') << setw(2) << ss;
	}
	else if (seconds >= 0){
		time_stream << setfill('0') << setw(2) << ss;
	}

	time_out = time_stream.str();
	return time_out;
}

int main(int argc, char* argv[]) {
    ifstream musicFile;
    string line, currentLineString, artistName, albumName, songName, min, sec;
	int song_time, trackNum;

    vector<Song> tempSongs;
    map<string, Artist> artists;

    musicFile.open(argv[1]);

    while (getline(musicFile, line)) {
        Song currentSong;

        // get full line from file to split whitespace
        stringstream ss;
        ss << line;

        // song title
        getline(ss, songName, ' ');
        replace(songName.begin(), songName.end(), '_', ' ');
        currentSong.title = songName;
		
		// song time
        getline(ss, min, ':');
		getline(ss, sec, ' ');
		//Convert to total seconds
		song_time = (stoi(sec) + (60 * stoi(min)));

//		cout << song_time << endl;

		currentSong.time = str_time(song_time);

        // song artist (add song to album and album to artist)
        getline(ss, artistName, ' ');
        replace(artistName.begin(), artistName.end(), '_', ' ');

        artists[artistName].name = artistName;
        artists[artistName].time += song_time;
        artists[artistName].nsongs++;

        getline(ss, albumName, ' ');
        replace(albumName.begin(), albumName.end(), '_', ' ');
        artists[artistName].albums[albumName].name = albumName;
        artists[artistName].albums[albumName].time += song_time;
        artists[artistName].albums[albumName].nsongs++;

        getline(ss, currentLineString, ' ');
        getline(ss, currentLineString, ' ');
        trackNum = stoi(currentLineString);

        artists[artistName].albums[albumName].songs[trackNum].title = currentSong.title;
        artists[artistName].albums[albumName].songs[trackNum].time = currentSong.time;
    }
    
    for (auto itr = artists.begin(); itr != artists.end(); ++itr) {
        cout << itr->first << ": " << itr->second.nsongs << ", " << str_time(itr->second.time) << endl;

        for (auto albumsItr = itr->second.albums.begin(); albumsItr != itr->second.albums.end(); ++albumsItr) {
            cout << "        " << albumsItr->first << ": " << albumsItr->second.nsongs << ", " << str_time(albumsItr->second.time) << endl;

            for (auto songsItr = albumsItr->second.songs.begin(); songsItr != albumsItr->second.songs.end(); ++songsItr) {
            	cout << "                " << songsItr->first << ". " << songsItr->second.title << ": " << songsItr->second.time << endl;
        	}
        }
    }
    musicFile.close();

    return 0;
}
