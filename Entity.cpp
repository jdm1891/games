#include "Entity.h"

#include <string>

#include <SFML\Graphics.hpp>


void Entity::update()
{

}

void Entity::init(std::string filepath, sf::Vector2f size)
{
	size.x == 0 ? size.x++ : size.x = size.x;
	size.y == 0 ? size.y++ : size.y = size.y;
	_size = size;
	_texture.loadFromFile(filepath);
	setTexture(_texture);
	setScale(size.x / _texture.getSize().x, size.y / _texture.getSize().y);
}

Entity::Entity()
{

}

Entity::~Entity()
{
}