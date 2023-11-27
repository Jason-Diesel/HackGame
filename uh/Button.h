#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::Drawable
{
public:
	Button(sf::Color buttonColor, sf::Vector2f position, sf::Vector2f size);
	bool clicked();
	bool hover();
	virtual void update(sf::Window& win);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void changeColor(sf::Color buttonColor);
protected:
	sf::RectangleShape rectangle;
	float mousex, mousey;
	bool click;
	bool firstPress;
};

class TextButton : public Button
{
public:
	TextButton(sf::Color buttonColor, sf::Vector2f position, sf::Vector2f size, sf::Text text);
	void changeText(std::string text);
	void changeText(sf::Text text);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Text text;
};

class Slider : public Button
{
public:
	Slider(sf::Color buttonColor, sf::Vector2f position, sf::Vector2f size, float max,
		sf::Color pointColor, float pointSize, float pointPosition = 1);
	~Slider();
	void update(sf::Window& win);
	float getCurrentPoint();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	float max;
	float pointPosition;
	sf::CircleShape point;
};