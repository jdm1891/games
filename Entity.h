#include <string>

#include <SFML\Graphics.hpp>

enum class TileID;

class Entity : public sf::Sprite
{
public:
	enum class EntityTexture{ PLAYER, ENEMY, NUMBER_OF_TYPES};
	void update();
	void init(std::string filepath = "set.png", sf::Vector2f size = sf::Vector2f(20, 20));
	Entity();
	~Entity();
private:
	sf::Texture _texture;
	sf::Vector2f _size;

};

