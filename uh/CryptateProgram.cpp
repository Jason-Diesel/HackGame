#include "CryptateProgram.h"
#include <iostream>

std::string encrypt(const std::string& message, int shift) {
	std::string encryptmessage;
	encryptmessage.resize(message.size());
	for (int i = 0; i < message.size(); i++)
	{
		int a = message[i] - 65;//make it from 0 - 25
		a += shift;
		while (a > 25)
		{
			a -= 25;
		}
		encryptmessage[i] = a + 65;//A-Z
	}
	return encryptmessage;
}

std::string decrypt(const std::string& ciphertext, int shift) {
	std::string decryptmessage;
	decryptmessage.resize(ciphertext.size());
	for (int i = 0; i < ciphertext.size(); i++) {
		int a = ciphertext[i] - 65; // Make it from 0 - 25
		a -= shift;
		// Use modulo to ensure the result is within the range 0 to 25
		while (a < 0)
		{
			a += 25;
		}
		decryptmessage[i] = a + 65; // make it A-Z
	}
	return decryptmessage;
}

CryptateProgram::CryptateProgram(const std::string& windowName):
	VirtualPrograms(windowName, sf::Vector2i(0,0), sf::Vector2u(800,800))
{
	timeLeft = 160.f;

	//create the encryption
	int specialNr = (rand() % 90) + 10;
	const uint16_t nrOfLetters = 10;
	decryptcode.resize(10);
	std::string letters;
	letters.resize(nrOfLetters);

	//65->90 diff = 26
	for(int i = 0; i < nrOfLetters; i++)
	{
		int rn = (rand() % 26) + 65;
		letters[i] = rn;
	}

	letters = encrypt(letters, specialNr);
	decryptcode = decrypt(letters, specialNr);
	CryptCode.setString(std::to_string(specialNr) + std::string(letters));
	
}

CryptateProgram::~CryptateProgram()
{
}

void CryptateProgram::init()
{
	CryptCode.setFont(rm->getFont("../Fonts/HappyMonkey-Regular.ttf"));
	encryptText.setFont(rm->getFont("../Fonts/HappyMonkey-Regular.ttf"));
	TimeLeftText.setFont(rm->getFont("../Fonts/HappyMonkey-Regular.ttf"));
	background = rm->getSprite("../Textures/CryptingBackground.png");

	encryptText.setString("");
	TimeLeftText.setString(std::to_string(timeLeft));

	sf::Color black = sf::Color::Black;

	CryptCode.setFillColor(black);
	encryptText.setFillColor(black);
	TimeLeftText.setFillColor(black);

	CryptCode.setCharacterSize(50);
	encryptText.setCharacterSize(50);
	TimeLeftText.setCharacterSize(50);

	CryptCode.setPosition(75,520);
	encryptText.setPosition(75,690);
	TimeLeftText.setPosition(450,200);
}

VirtualProgramReturn CryptateProgram::update(float dt)
{
	timeLeft -= dt;
	TimeLeftText.setString(std::to_string(timeLeft));
	if(timeLeft < 0) {return VirtualProgramReturn::Hacked;}

	if(!this->window.hasFocus()) {return VirtualProgramReturn::Continue;}

	if(decryptcode == encryptString)
	{
		window.close();
		return VirtualProgramReturn::Exit;
	}


	return VirtualProgramReturn::Continue;
}

void CryptateProgram::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::TextEntered) {
	        if (event.text.unicode >= 32 && event.text.unicode < 127) {
	            encryptString += static_cast<char>(event.text.unicode);
				encryptText.setString(encryptString);
	        }
	    }
		else if (event.type == sf::Event::KeyPressed) {
	        if (event.key.code == sf::Keyboard::BackSpace && !encryptString.empty()) {
	            encryptString.pop_back();
				encryptText.setString(encryptString);
	        }
	    }
	}
}

void CryptateProgram::draw()
{
	window.clear();

	window.draw(background);
	window.draw(CryptCode);
	window.draw(encryptText);
	window.draw(TimeLeftText);

	window.display();
}

