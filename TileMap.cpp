#include "stdafx.h"


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
	_textureSize.y = _textureSize.x;

	//Set other variables
	_width = width;
	_height = height;
	_level = level; 
	_fillStyle = fillStyle;
	_tileSize = tileSize;
	_textureFileName = fileName;
	_TotalSize.width = width*tileSize.x;
	_TotalSize.height = height*tileSize.y;

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
	int numberOfVariations = -1;

	//_texture.getSize().y / _height = the maximum number of tile variations for each tile
	for (int i = 0; i < _tileSize.y; i++)
	{
		//If *current tile* pixel is transparent(the tile doesn't exist)
		if (image.getPixel((int)(tileType)*_tileSize.x, i*_tileSize.y).a == 0)
		{
			//That is the number of tile variations
			numberOfVariations = i;
			//End for loop
			break;
		}
	}

	//Random generator
	std::default_random_engine generator;

	generator.seed((++x)*(++y)+(++x));

	//need to multiply by tile size, as to make it work
	std::uniform_int_distribution<int> distribution(1, numberOfVariations);
	
	int variation = distribution(generator);
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
			int variation = createVariation(i, j);
            // get the current tile number
            int tileNumber = (int)_level[i + j * _width];

            // find its position in the tileset texture - need to be square!!!
			int texSize = std::floor(_texture.getSize().x / _textureSize.x);
            int tu = tileNumber %  texSize;

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &_vertex[(i + j * _width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(std::round(i * _textureSize.x), std::round(j * _textureSize.y));
            quad[1].position = sf::Vector2f(std::round((i + 1) * _textureSize.x), std::round(j * _textureSize.y));
            quad[2].position = sf::Vector2f(std::round((i + 1) * _textureSize.x), std::round((j + 1) * _textureSize.y));
            quad[3].position = sf::Vector2f(std::round(i * _textureSize.x), std::round((j + 1) * _textureSize.y));

            // define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(std::round(tu * _textureSize.x), std::round(_textureSize.y*(variation-1)));
			quad[1].texCoords = sf::Vector2f(std::round((tu + 1) * _textureSize.x), std::round(_textureSize.y*(variation-1)));
            quad[2].texCoords = sf::Vector2f(std::round((tu + 1) * _textureSize.x), std::round(_textureSize.y*variation));
            quad[3].texCoords = sf::Vector2f(std::round(tu * _textureSize.x),std::round(_textureSize.y*variation) );
        }
		if (i % 50 == 0)
		{
			std::cout << i << std::endl;
		}
	}
	 std::cout << _textureSize.x << std::endl;
	 std::cout << _textureSize.y << std::endl;
}

//////////////////////////////////////////////////////////////////////
///draw:		Only use if you are planning on using a fillstyle, or another preprocessing option
void TileMap::draw(sf::RenderWindow &window)
{
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

		//Find size of each tile in texture | total size of texture devided by the number of different textures | must be square
		_textureSize.x = (_texture.getSize().x) / (int)TileID::NUMBER_OF_TYPES;
		_textureSize.y = _textureSize.x;
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

TotalSize TileMap::getTotalSize()
{
	return _TotalSize;
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
