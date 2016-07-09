#pragma once
#include <vector>
#include <string>
#include <SFML/Audio.hpp>


class Playlist
{
public:
	Playlist();
	void loadDefault();
	void addSong(std::string filepath);
	void start();
	void pause();
	void skipSong();
private:
	//To play music
	sf::Music _music;

	//List of filenames to load
	std::vector<std::string> _files;

	//Compatilbe audio formats
	std::vector<std::string> _compatibleFormats;
};

