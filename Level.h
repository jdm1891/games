#pragma once
#include <SFML\Graphics.hpp>
#include "TileMap.h"

struct Level
{
	TileMap levelData;
	TileID *tileData;
	void draw(sf::RenderWindow *window)
	{
		levelData.draw(*window);
	}
	///Do not use levelData.init by itself! If you do, use levelData.getTileData() and not structName.tileData
	void init(int width, int height, TileID *level, sf::Vector2u tileSize, FillStyle fillStyle, std::string fileName)
	{
		levelData.init(width, height, level, tileSize, fillStyle, fileName);
		tileData = level;
	}
};