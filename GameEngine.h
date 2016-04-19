#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Level.h"

enum GameState { PLAY, PAUSE, QUIT };

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	sf::VideoMode getGameBorder();
	void run();

private:
	
	//Functions
	void processEvents();
	void processKeyboardInput();
	void draw();
	void physics();
	
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

	Entity player;
};