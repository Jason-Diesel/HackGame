#include "MatrixRainDrop.h"

MatrixRainDrop::MatrixRainDrop(sf::Vector2f wh, sf::Font& font)
{
	maxTimeForNextUpdate = ((float)(rand() % 5) + 1) * 0.05f;

	color = sf::Color::Green;
	float xPosition = (float)((rand() % (int)wh.x)) ;
	float yPosition = (float)(-(rand() % 200));
	for (int i = 0; i < nrOfCharcters; i++)
	{
		sf::Color newColor = color;
		newColor.a = newColor.a * i / nrOfCharcters;
		MatrixRain[i].setFont(font);
		MatrixRain[i].setFillColor(newColor);
		MatrixRain[i].setCharacterSize((rand() % 6) + 18);
		MatrixRain[i].setPosition(xPosition, yPosition + (i * distanceBetween));
		char c = (rand() % 57) + 65;
		MatrixRain[i].setString(c);
	}
}

void MatrixRainDrop::update(float dt)
{
	timeForNextUpdate += dt;
	if (timeForNextUpdate < maxTimeForNextUpdate){return;}

	timeForNextUpdate = 0;

	currentCharacter += 1;
	currentCharacter = currentCharacter % nrOfCharcters;

	for (int i = 0; i < nrOfCharcters; i++)
	{
		sf::Color newColor = color;
		newColor = MatrixRain[i].getFillColor();
		newColor.a -= (int)((1.f / (nrOfCharcters-1)) * 255.f);
		MatrixRain[i].setFillColor(newColor);
	}
	MatrixRain[currentCharacter].setFillColor(color);
}

void MatrixRainDrop::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < nrOfCharcters; i++)
	{
		target.draw(MatrixRain[i]);
	}
}
