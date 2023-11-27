#pragma once
#include "VirtualPrograms.h"

class MovingProgram : public VirtualPrograms
{
public:
	MovingProgram(const std::string& windowName);
	void init();
	VirtualProgramReturn update(float dt);
	void draw();
	void handleEvents();

private:
	sf::Text nrOfClosesLeftText;
	sf::Sprite background;

	int nrOfClosesNeededLeft;
	const int maxNrOfCloses = 20;

	const float updateMoreCloses = 4.0f;
	float currentUpdateMoreCloses = 0;
};