#include "Playlist.h"
#include "Filesystem.h"
#include <iostream>
#include <random>


Playlist::Playlist()
{
	_compatibleFormats = {	".ogg", ".wav", ".flac", ".aiff", ".au", ".raw",
							".paf", ".svx", ".nist", ".voc", ".ircam", ".w64",
							".mat4", ".mat5", ".pvf", ".htk", ".sds", "avr",
							".sd2", ".caf", ".wve", ".mpc2k", ".rf64", ".WAV" };
}

void Playlist::loadDefault()
{
	//Find songs in the music folder and put them into the song index
	auto songIndex = Filesystem::scan("./resources/music" , _compatibleFormats);
	//ogg, wav, flac, aiff, au, raw, paf, svx, nist, voc, ircam, w64, mat4, mat5 pvf, htk, sds, avr, sd2, caf, wve, mpc2k, rf64.
	//Are compatible audio formats
	//For each song in the song index
	for (const auto& filepath : songIndex)
	{
		//Add the song
		addSong(filepath);
		std::cout << "Loaded music:" << filepath << std::endl;
	}
}

void Playlist::addSong(std::string filepath)
{
	_files.push_back(filepath);
}

void Playlist::start()
{
	if (_music.getStatus() == sf::Music::Stopped)
	{
		//Make only one instance of the generator - with time for the seed
		static std::default_random_engine engine;
		engine.seed(time(nullptr));
		static std::uniform_int_distribution<int> distribution(0, _files.size() - 1);
		if (_files.size() != 0)
		{
			std::string filepath = _files[distribution(engine)];
			_music.openFromFile(filepath);
			_music.play();
			std::cout << "Now playing song: " << filepath << std::endl;
		}
		else
		{
			std::cout << "Failed to play music: No music found!" << std::endl;
		}
	}
	else if (_music.getStatus() == sf::Music::Paused)
	{
		_music.play();
	}
}

void Playlist::pause()
{
	_music.pause();
}

void Playlist::skipSong()
{
	//Stops the stream and starts a new one - effectivly skipping the current song
	_music.stop();
	start();
}
