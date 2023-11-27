#include "VirtualPrograms.h"

VirtualPrograms::VirtualPrograms(const std::string& windowName, sf::Vector2i windowPos, sf::Vector2u windowSize):
	window(sf::VideoMode(windowSize.x, windowSize.y), windowName.c_str()),
	deletedWindow(false)
{
	window.setPosition(windowPos);
}

VirtualPrograms::~VirtualPrograms()
{
}

void VirtualPrograms::init()
{
}

void VirtualPrograms::setRandomPosition()
{
	sf::Vector2i pos;
	pos.x = rand() % (sf::VideoMode::getDesktopMode().width - window.getSize().x);
	pos.y = rand() % (sf::VideoMode::getDesktopMode().height - window.getSize().y);
	this->window.setPosition(pos);
}

void VirtualPrograms::addResourceManager(ResourceManager* rm)
{
	this->rm = rm;
}

VirtualProgramReturn VirtualPrograms::update(float dt)
{
	return VirtualProgramReturn::Continue;
}

void VirtualPrograms::draw()
{
}

void VirtualPrograms::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			deletedWindow = true;
			window.close();
		}
	}
}
