#pragma once

#include "GameEngine.h"
#include "TileMap.h"
#include "Playlist.h"
#include "PauseMenu.h"
#include <SFML/Graphics.hpp>
#define GAMEWIDTH sf::VideoMode::getDesktopMode().width*0.9
#define GAMEHEIGHT sf::VideoMode::getDesktopMode().height*0.9

enum GameState { PLAY, PAUSE, QUIT, SUSPENDED };

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	sf::VideoMode getGameBorder();
	GameState getGameState();
	sf::RenderWindow& window();
	void run();

private:
	
	//Functions
	void processEvents();
	void processKeyboardInput();
	void draw();
	void physics();
	void checkIfUnpaused();
	void updateView();
	
	//Stuff for window
	sf::RenderWindow _window;
	sf::ContextSettings _settings;

	//Screen and game size
	sf::VideoMode _screenBorder;
	sf::VideoMode _gameBorder;

	//Event
	sf::Event _event;

	//Game state
	GameState _gameState;

	//Tile Map
	TileMap _level;
	sf::RenderTexture _levelRender;

	//player
	Entity _player;

	//Music player
	Playlist _musicPlayer;

	//View
	sf::View _view;

	//Pause menu
	PauseMenu _pauseMenu;
};