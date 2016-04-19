#include "ImageToTileID.h"
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

std::vector<TileID> ImageToTileID::ConvertToArray(std::string filepath)
{
	sf::Image image;
	//Load the image from filepath provided
	image.loadFromFile(filepath);

	//A vector of pairs
	std::vector<std::pair<TileID, sf::Color>> TileToColor;

	//Define the pairs
	TileToColor.emplace_back(TileID::WATER, sf::Color(0, 0, 255, 255));
	TileToColor.emplace_back(TileID::GRASS, sf::Color(0, 0, 25, 255));
	TileToColor.emplace_back(TileID::ERROR_TILE, sf::Color(0, 0, 0, 0));

	//Checks if all tiles have been mapped!
		if (TileToColor.size() != (int)TileID::NUMBER_OF_TYPES)
		{
			//Creates and returns an empty vector
			return notFound();
		}

	//Creates the container for data to return
	std::vector<TileID> container(image.getSize().x*image.getSize().y);
	if (image.getSize().x == 0 || image.getSize().y == 0)
	{
		return notFound();
	}
	for (int i = 0; i < image.getSize().x; i++)
	{
		for (int j = 0; j < image.getSize().y; j++)
		{
			for (int k = 0; k < (int)TileID::NUMBER_OF_TYPES; k++)
			{
				if (image.getPixel(i, j) == TileToColor[k].second)
				{
					container[i + j*image.getSize().x] = TileToColor[k].first;
				}
			}
		}
		std::cout << std::endl;
	}
	std::cout << container.size() << std::endl;
	//Return vector
	return container;
}

std::vector<TileID> ImageToTileID::notFound()
{
	std::vector<TileID> a = { TileID::ERROR_TILE };
	return a;
}
