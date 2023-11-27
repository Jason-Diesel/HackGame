#include "MovingProgram.h"

MovingProgram::MovingProgram(const std::string& windowName):
    VirtualPrograms(windowName, sf::Vector2i(0,0), sf::Vector2u(300, 300))
{
    this->setRandomPosition();
}

void MovingProgram::init()
{
	nrOfClosesNeededLeft = (rand() % 10) + 5;
	background = rm->getSprite("../Textures/BubbleBackground.png");
	background.setScale(0.3f, 0.3f);

	nrOfClosesLeftText.setFont(rm->getFont("../Fonts/Agbalumo-Regular.ttf"));
	nrOfClosesLeftText.setFillColor(sf::Color::Yellow);
	nrOfClosesLeftText.setCharacterSize(40);
	nrOfClosesLeftText.setString(std::to_string(nrOfClosesNeededLeft));
	nrOfClosesLeftText.setPosition(125,135);
	
}

VirtualProgramReturn MovingProgram::update(float dt)
{
	currentUpdateMoreCloses += dt;
	if(currentUpdateMoreCloses > updateMoreCloses)
	{
		currentUpdateMoreCloses = 0;
		nrOfClosesNeededLeft++;
		nrOfClosesLeftText.setString(std::to_string(nrOfClosesNeededLeft));
	}

	if(nrOfClosesNeededLeft > maxNrOfCloses) {return VirtualProgramReturn::Hacked;}

	if(nrOfClosesNeededLeft <= 0) {
		window.close();
		return VirtualProgramReturn::Exit;
	}

    return VirtualProgramReturn::Continue;
}

void MovingProgram::draw()
{
	window.clear();

	window.draw(background);

	nrOfClosesLeftText.setCharacterSize(41);
	nrOfClosesLeftText.setFillColor(sf::Color::Black);
	window.draw(nrOfClosesLeftText);
	nrOfClosesLeftText.setCharacterSize(40);
	nrOfClosesLeftText.setFillColor(sf::Color::Yellow);
	window.draw(nrOfClosesLeftText);

	window.display();
}

void MovingProgram::handleEvents()
{
    sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			currentUpdateMoreCloses = 0;
			nrOfClosesNeededLeft--;
			nrOfClosesLeftText.setString(std::to_string(nrOfClosesNeededLeft));
			if(nrOfClosesNeededLeft > 0)
			{
				this->setRandomPosition();
			}
		}
	}
}
