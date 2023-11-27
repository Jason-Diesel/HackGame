#pragma once
#include <SFML/Graphics.hpp>

class MatrixRainDrop : public sf::Drawable
{
public:
	MatrixRainDrop(sf::Vector2f wh, sf::Font& font);
	void update(float dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Color color;
	int currentCharacter = 0;
	float distanceBetween = 24;

	static const int nrOfCharcters = 20;
	sf::Text MatrixRain[nrOfCharcters];
	sf::Vector2f position;

	float maxTimeForNextUpdate;
	float timeForNextUpdate = 0;
};