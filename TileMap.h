#pragma once
#include "Entity.h"
#include "SmartEnum.h"
#include <SFML/Graphics.hpp>
#include <string>

//Entity forward declaration
class Entity;

//Types of tiles
enum class TileID { GRASS, WATER, ERROR_TILE, NUMBER_OF_TYPES };

//Fill style: FILL-Strech to fill screen	| REPEAT-Don't strech	| NONE-No effects
enum class FillStyle { /*DEBUG ONLY*/ FILL, /*NOT YET IMPLEMENTED*/ REPEAT, NONE};

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	///////////////////////////////////////////////////////////////////////////////////
	///	TileMap:	this does nothing important
	///////////////////////////////////////////////////////////////////////////////////
	TileMap();

	///////////////////////////////////////////////////////////////////////////////////
	///	init:		this initialises the tiles by setting the variables and
	///				creating the vertex array, stored privatly at _vertex. 
	///				Places a pointer to the level stored at _level			
	///////////////////////////////////////////////////////////////////////////////////
	void init	(
				int width, 
				int height, 
				TileID *level,
				sf::Vector2u tileSize, 
				FillStyle fillStyle	,
				std::string fileName
				);
	
	///////////////////////////////////////////////////////////////////////////////////
	/// draw:		this should be used instead of window.draw(), as this
	///				injects code before calling the function before calling
	///				window.draw(). It puts in code to ignore transformations
	///				and things that are required to be done from the class 
	///				itself and not from the window
	///////////////////////////////////////////////////////////////////////////////////
	void draw	(sf::RenderWindow &window);

	///////////////////////////////////////////////////////////////////////////////////
	/// update:		this updates the tilemap in another thread. it does this as
	///				to not interrupt the game while switching the textures. it
	///				is advised to use this instead of making an entirely new 
	///				array for small changes.
	///////////////////////////////////////////////////////////////////////////////////
	void update();

	///////////////////////////////////////////////////////////////////////////////////
	///	updateTextures:		this updates what textures are used for the TileMap
	///						doing this allows you to change the style of the world
	///						or allow alternate colour blind textures. ect. 
	///						This takes a file name to the new path; if it is
	///						the same nothing is done in order to save resources				
	///////////////////////////////////////////////////////////////////////////////////
	void updateTextures(std::string fileName);

	///////////////////////////////////////////////////////////////////////////////////
	/// getTileData:		Returns a pointer to the tile Data (Type TileID)
	///
	///////////////////////////////////////////////////////////////////////////////////
	TileID* getTileData();

	///////////////////////////////////////////////////////////////////////////////////
	///findOccupyingTiles:	Find the tile(s) an entity if currently occupying and if they're allowed
	///////////////////////////////////////////////////////////////////////////////////
	void findOccupingTiles(Entity &entity);

	~TileMap();
protected:

	//Create, called by init
	void create();

	//Draw
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//Fill Stylep
	FillStyle _fillStyle;

	//Amount of tiles width and height
	int _width;
	int _height;

	//Tile size
	sf::Vector2u _tileSize;

	//Texture Size
	sf::Vector2i _textureSize;

	//Level data
	TileID *_level;

	//Vertex Array
	sf::VertexArray _vertex;

	//Texture
	sf::Texture _texture;

	//Game Border
	sf::VideoMode _gameBorder;

	//File name
	std::string _textureFileName;


};

