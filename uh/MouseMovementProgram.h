#pragma once
#include "VirtualPrograms.h"

class MouseMovementProgram : public VirtualPrograms
{
public:
	MouseMovementProgram(const std::string& windowName);
	void init();
	VirtualProgramReturn update(float dt);
	void draw();
private:
	float nextUpdate = 0;
	float maxTimeUntilUpdate = 0.01f;
	sf::Text text;
};