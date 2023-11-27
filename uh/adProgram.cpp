#include "adProgram.h"

adProgram::adProgram(const std::string& windowName, sf::Vector2i windowPos, sf::Vector2u windowSize):
	VirtualPrograms::VirtualPrograms(windowName, windowPos, windowSize)
{
}

void adProgram::init()
{
	sprite = rm->getSprite("../Textures/Vedal.png");
	sprite.setPosition(0, 0);
	sprite.setScale(0.7, 0.7);

	hot.setFont(rm->getFont("../Fonts/HappyMonkey-Regular.ttf"));
	hot.setCharacterSize(24);
	hot.setFillColor(sf::Color::Black);
	hot.setString("Hot Turtles in your area ;)");
	hot.setPosition(100, 350);
}

VirtualProgramReturn adProgram::update(float dt)
{
	if(deletedWindow)
	{
		return VirtualProgramReturn::Exit;
	}

	return VirtualProgramReturn::Continue;
}

void adProgram::draw()
{
	window.clear();

	window.draw(sprite);
	window.draw(hot);

	window.display();
}
