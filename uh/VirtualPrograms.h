#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include "ResourceManager.h"
#include <thread>

enum class VirtualProgramReturn
{
Continue,
Exit,
Hacked
};

class VirtualPrograms
{
public:
	VirtualPrograms(const std::string& windowName, sf::Vector2i windowPos, sf::Vector2u windowSize);
	virtual ~VirtualPrograms();
	virtual void init();
	void setRandomPosition();
	void addResourceManager(ResourceManager* rm);
	virtual VirtualProgramReturn update(float dt);
	virtual void draw();
	virtual void handleEvents();
protected:
	sf::RenderWindow window;
	bool deletedWindow;
	ResourceManager* rm;
};