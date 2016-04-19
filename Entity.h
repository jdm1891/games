#pragma once
#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include <string>

enum class TileID;

class Entity : public sf::Sprite
{
public:
	void update();
	void init(std::string filepath = "set.png", sf::Vector2f size = sf::Vector2f(20, 20));
	Entity();
	~Entity();
private:
	sf::Texture _texture;
	sf::Vector2f _size;

};

