#pragma once
#include <SFML/Graphics.hpp>

class PauseMenu : public sf::Drawable
{
public:
	PauseMenu();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::RectangleShape _background;
};