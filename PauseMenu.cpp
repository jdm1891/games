#include "GameEngine.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
	_background.setFillColor(sf::Color(0, 0, 0, 128));
	_background.setSize(sf::Vector2f(GAMEWIDTH, GAMEHEIGHT));
}

void PauseMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Draw all pause menu objects onto screen
	target.draw(_background, states);
}
