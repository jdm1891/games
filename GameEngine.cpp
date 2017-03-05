#include "GameEngine.h"
#include "Playlist.h"
#include "ImageToTileID.h"
#include "TileMap.h"
#include <SFML\Graphics.hpp>

/*

N£ED TO:

	collision detection

	TileMap::GetTile2D(Function that returns tileID of an x,y coordinate)
	
	Sort out GameEngine.Cpp & h - remove junk


*/

GameEngine::GameEngine()
{
	//GameState = Play
	_gameState = PLAY;

	//Set size of game window(90% of width & height)
	_screenBorder = sf::VideoMode::getDesktopMode();
	_gameBorder = sf::VideoMode(GAMEWIDTH, GAMEHEIGHT);
	//Create level
	
	_level.init(50, 50, &ImageToTileID::ConvertToArray("./level/test.png")[0], sf::Vector2u(32, 32), FillStyle::FILL, "./level/set5.png");

	//Set up Level Render

	_levelRender.create(_level.getTotalSize().width, _level.getTotalSize().height);

	//View - make centre half of size to start at top left
	_view.setCenter(sf::Vector2f((double)_level.getTotalSize().width/2, (double)_level.getTotalSize().height/2));
	_view.setSize(sf::Vector2f((double)_level.getTotalSize().width/3 , (double)_level.getTotalSize().height/3));

	//Create the player
	///

	//Window
	_settings.antialiasingLevel = 8;
	_window.create(_gameBorder, "Pacman", sf::Style::None, _settings);
	_window.setVerticalSyncEnabled(true);

	//Set window to be visible
	_window.setPosition(sf::Vector2i(_window.getPosition().x, _window.getPosition().y - _screenBorder.height*0.02));

	//Start the music player
	_musicPlayer.loadDefault();
	_musicPlayer.start();

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

GameState GameEngine::getGameState()
{
	return _gameState;
}

sf::RenderWindow & GameEngine::window()
{
	return _window;
}

void GameEngine::run()
{
	while (_window.isOpen())
	{
		switch (_gameState)
		{
		case PLAY:
			processEvents();
			draw();
			physics();
			updateView();
			break;

		case PAUSE:
			checkIfUnpaused();
			_window.clear();
			draw();
			_window.draw(_pauseMenu);
			_window.display();
			break;

		case QUIT:
			exit(0);
			break;

		case SUSPENDED:
			checkIfUnpaused();
			_musicPlayer.pause();
			break;
		default: 
			exit(1);
		}
		sf::sleep(sf::milliseconds(1));
	}
}

void GameEngine::processEvents()
{
	while (_window.pollEvent(_event))
	{
		switch (_event.type)
		{
		case sf::Event::KeyPressed:
			processKeyboardInput();
			break;
		
		case sf::Event::Closed:
			_gameState = QUIT;
			break;

		case sf::Event::LostFocus:
			_gameState = SUSPENDED;
			break;

		case sf::Event::GainedFocus:
			_gameState = PLAY;
			break;

		default:
			break;
		}
	}

}

void GameEngine::processKeyboardInput()
{
	//Speed per second
	static float m = 5;
	if (_event.key.code == sf::Keyboard::Escape)
	{
		_gameState = PAUSE;
		return;
	}
	if (_event.key.code == sf::Keyboard::Up)
	{
		_view.move(0, -m);
		return;
	}
	if (_event.key.code == sf::Keyboard::Down)
	{
		_view.move(0, m);
		return;
	}
	if (_event.key.code == sf::Keyboard::Left)
	{
		_view.move(-m, 0);
		return;
	}
	if (_event.key.code == sf::Keyboard::Right)
	{
		_view.move(m, 0);
		return;
	}
}

void GameEngine::draw()
{
	_levelRender.clear(sf::Color::Yellow);
	_levelRender.draw(_level);
	_levelRender.display();

	//Only clear when not paused
	if (_gameState != PAUSE)
	{
		_window.clear(sf::Color::Yellow);
	}
	
	//Draw commands
	_window.draw(sf::Sprite(_levelRender.getTexture()));

	//Only display when not paused
	if (_gameState != PAUSE)
	{
		_window.display();
	}
}

void GameEngine::physics()
{
	_level.findOccupingTiles(_player);
	_musicPlayer.start();
}

void GameEngine::checkIfUnpaused()
{
	while (_window.pollEvent(_event))
	{
		switch (_event.type)
		{
		case sf::Event::KeyPressed:
			if (_event.key.code == sf::Keyboard::Escape)
			{
				_gameState = PLAY;
			}
			break;
		case sf::Event::LostFocus:
			_gameState = SUSPENDED;
			break;
		case sf::Event::GainedFocus:
			_gameState = PAUSE;
			_musicPlayer.start();
			break;
		default:
			break;
		}
	}
}

void GameEngine::updateView()
{
	_view.move(sin(time(nullptr)),(cos(time(nullptr))));
	_levelRender.setView(_view);
}



