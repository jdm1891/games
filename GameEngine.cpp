#include "GameEngine.h"
#include "TileMap.h"
#include "StaticLevelData.h"
#include "ImageToTileID.h"
#include <iostream>


/*

N£ED TO:

collision detection
{
	find position of all four corners and see if they touch a bad tile, if they do
	prohibit movement of entity.

	create classes:
		Player			:	entity
		Enemy			:	entity
		FlyingEntity	:	entity
		FlyingEnemy		:	FlyingEntity
		
		Tile2D	- takes a coordinate, and returns the tile number that coordinate lands on(takes a &TileMap and a 
		
}


*/

GameEngine::GameEngine()
{
	//GameState = Play
	_gameState = PLAY;

	//Set size of game window(90% of width & height)
	_screenBorder = sf::VideoMode::getDesktopMode();
	_gameBorder = sf::VideoMode(_screenBorder.width*0.9, _screenBorder.height*0.9);
	
	//Window
	_settings.antialiasingLevel = 8;
	_window.create(_gameBorder, "Pacman", sf::Style::None, _settings);
	_window.setVerticalSyncEnabled(true);
	//Set window to be visible
	_window.setPosition(sf::Vector2i(_window.getPosition().x, _window.getPosition().y-_screenBorder.height*0.02));
	 
	//Create level
	
	_level.init(50, 50, &ImageToTileID::ConvertToArray("./level/test.png")[0], sf::Vector2u(20, 20), FillStyle::FILL, "set.png");

	player.init("set2.png", sf::Vector2f(10, 10));
	player.setPosition(0, 0);
	//Run the game
	run();

}


GameEngine::~GameEngine()
{
}

sf::VideoMode GameEngine::getGameBorder()
{

	return _gameBorder;
}

void GameEngine::run()
{
	while (true)
	{
		switch (_gameState)
		{
		case PLAY:
			processEvents();
			draw();
			physics();
			break;

		case PAUSE:
			break;

		case QUIT:
			exit(0);
		default:
			exit(1);
		}
		sf::sleep(sf::milliseconds(1));
	}
}

void GameEngine::processEvents()
{
	if (_window.pollEvent(_event))
	{
		switch (_event.type)
		{
		case sf::Event::Closed:
			_gameState = QUIT;
			break;

		case sf::Event::LostFocus:
			_gameState = PAUSE;
			break;

		case sf::Event::GainedFocus:
			_gameState = PLAY;
			break;

		case sf::Event::KeyPressed:
			processKeyboardInput();
			break;

		default:
			break;
		}
	}

}

void GameEngine::processKeyboardInput()
{
	if (_event.key.code == sf::Keyboard::Escape)
	{
		_gameState = QUIT;
		return;
	}
	if (_event.key.code == sf::Keyboard::Up)
	{
		player.move(0, -1);
	}
	if (_event.key.code == sf::Keyboard::Down)
	{
		player.move(0, 1);
	}
	if (_event.key.code == sf::Keyboard::Left)
	{
		player.move(-1, 0);
	}
	if (_event.key.code == sf::Keyboard::Right)
	{
		player.move(1, 0);
	}
}

void GameEngine::draw()
{
	_window.clear(sf::Color::Yellow);
	_window.draw(_level);
	_window.draw(player);
	_window.display();
}

void GameEngine::physics()
{
	_level.findOccupingTiles(player);
}



