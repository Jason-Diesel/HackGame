#pragma once
#include "VirtualPrograms.h"

class adProgram : public VirtualPrograms
{
public:
	adProgram(const std::string& windowName, sf::Vector2i windowPos, sf::Vector2u windowSize);
	void init();
	VirtualProgramReturn update(float dt);
	void draw();
private:
	sf::Sprite sprite;
	sf::Text hot;
};