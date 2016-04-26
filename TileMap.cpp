#include "TileMap.h"
#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include <iostream>
#include <string>
#include <cmath>
#include <random>

GameEngine engine;
extern GameEngine engine;

TileMap::TileMap()
{
}

void TileMap::init(int width, int height, TileID * level, sf::Vector2u tileSize, FillStyle fillStyle, std::string fileName)
{
	//Load texture
	_texture.loadFromFile(fileName);

	//Find size of each tile in texture | total size of texture devided by the number of different textures
	_textureSize.x = (_texture.getSize().x) / (int)TileID::NUMBER_OF_TYPES;
	_textureSize.y = _texture.getSize().y;

	//Set other variables
	_width = width;
	_height = height;
	_level = level; 
	_fillStyle = fillStyle;
	_tileSize = tileSize;
	_textureFileName = fileName;

	//If set to fill screen ignore tile size
	if (_fillStyle == FillStyle::FILL)
	{
		_tileSize.x = _textureSize.x;
		_tileSize.y = _textureSize.y;
	}

	//Get size of game screen from engine (Sizes of everything are relitive to this as a way of handling resolutions)
	_gameBorder = engine.getGameBorder();

	create();
}


int TileMap::createVariation(int x, int y)
{
	TileID tileType = _level[x + y*_width];
	sf::Image image = _texture.copyToImage();
	int numberOfVariations = 0;

	//_texture.getSize().y / _height = the maximum number of tile variations for each tile
	for (int i = 0; i < (_texture.getSize().y / _height); i++)
	{
		//If *current tile* pixel is transparent(the tile doesn't exist)
		if (image.getPixel(((int)tileType) * 20, i*(_texture.getSize().y / _height)).a == 0)
		{
			//That is the number of tile variations
			numberOfVariations = i - 1;
			
			//skip the rest of the loop
			i = (_texture.getSize().y / _height) - 1;
		}
	}
	
	//Random generator
	std::default_random_engine generator;

	//need to multiply by tile size, as to make it work
	std::uniform_int_distribution<int> distribution(0, numberOfVariations);
	
	int variation = distribution(generator)*_tileSize.y;
	return variation;
}

void TileMap::create()
{
	//Set up vertex array
	_vertex.setPrimitiveType(sf::Quads);
	_vertex.resize(_width * _height * 4);

	 for (unsigned int i = 0; i < _width; ++i)
	 {
        for (unsigned int j = 0; j < _height; ++j)
        {
            // get the current tile number
            int tileNumber = (int)_level[i + j * _width];

            // find its position in the tileset texture - need to be square!!!
            int tu = tileNumber % ( _texture.getSize().x / _textureSize.x );
            int tv = tileNumber / ( _texture.getSize().x / _textureSize.x );

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &_vertex[(i + j * _width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * _textureSize.x, j * _textureSize.y);
            quad[1].position = sf::Vector2f((i + 1) * _textureSize.x, j * _textureSize.y);
            quad[2].position = sf::Vector2f((i + 1) * _textureSize.x, (j + 1) * _textureSize.y);
            quad[3].position = sf::Vector2f(i * _textureSize.x, (j + 1) * _textureSize.y);

            // define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * _textureSize.x, tv * (_textureSize.y + createVariation(i, j)));
			quad[1].texCoords = sf::Vector2f((tu + 1) * _textureSize.x, tv * (_textureSize.y + createVariation(i, j)));
            quad[2].texCoords = sf::Vector2f((tu + 1) * _textureSize.x, (tv + 1) * (_textureSize.y + createVariation(i, j)));
            quad[3].texCoords = sf::Vector2f(tu * _textureSize.x, (tv + 1) * (_textureSize.y + createVariation(i, j)));

        }
	}
}

//////////////////////////////////////////////////////////////////////
///draw:		Only use if you are planning on using a fillstyle, or another preprocessing option
void TileMap::draw(sf::RenderWindow &window)
{
	if (_fillStyle == FillStyle::FILL)
	{
		setScale((double)_gameBorder.width / (_tileSize.x*_width), (double)_gameBorder.height / (_tileSize.y*_height));
	}
	else
	{
		setScale((double)_tileSize.x / _textureSize.x, (double)_tileSize.y / _textureSize.y);
	}
	window.draw(*this);

}

void TileMap::update()
{
//	sf::Thread update_thread(&create);
//	update_thread.launch();
}

void TileMap::updateTextures(std::string fileName)
{
	if (fileName != _textureFileName)
	{
		//Load texture
		_texture.loadFromFile("./textures/" + fileName);

		//Find size of each tile in texture | total size of texture devided by the number of different textures
		_textureSize.x = (_texture.getSize().x) / (int)TileID::NUMBER_OF_TYPES;
		_textureSize.y = _texture.getSize().y;
	}
}

TileID* TileMap::getTileData()
{
	return _level;
}

void TileMap::findOccupingTiles(Entity &entity)
{
	//TBA
}

TileMap::~TileMap()
{
}

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//Apply transforfmation
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &_texture;

	// draw the vertex array
	target.draw(_vertex, states);
}
