#pragma once
#include "VirtualPrograms.h"

class CryptateProgram : public VirtualPrograms
{
public:
	CryptateProgram(const std::string& windowName);
	virtual ~CryptateProgram();
	void init();
	VirtualProgramReturn update(float dt);
	void handleEvents();
	void draw();
private:
	sf::Text CryptCode;
	std::string CryptCodeStr;
	std::string decryptcode;

	sf::Text encryptText;
	std::string encryptString;

	sf::Text TimeLeftText;
	float timeLeft;

	sf::Sprite background;
};