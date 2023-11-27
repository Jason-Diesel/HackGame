#include "Button.h"

Button::Button(sf::Color buttonColor, sf::Vector2f position, sf::Vector2f size)
{
    this->rectangle.setSize(size);
    this->rectangle.setOrigin(size.x / 2, size.y / 2);
    this->rectangle.setFillColor(buttonColor);
    this->rectangle.setPosition(position);
    click = false;
    firstPress = true;
}

bool Button::clicked()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (firstPress)
        {
            click = true;
        }
        else {
            click = false;
        }
        firstPress = false;
    }
    else
    {
        firstPress = true;
        click = false;
    }
    return hover() && click;
}

bool Button::hover()
{
    return mousex > rectangle.getGlobalBounds().left && mousex < rectangle.getGlobalBounds().left + rectangle.getGlobalBounds().width &&
        mousey > rectangle.getGlobalBounds().top && mousey < rectangle.getGlobalBounds().top + rectangle.getGlobalBounds().height;
}

void Button::update(sf::Window& win)
{
    mousex = (float)sf::Mouse::getPosition(win).x;
    mousey = (float)sf::Mouse::getPosition(win).y;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(this->rectangle);
}

void Button::changeColor(sf::Color buttonColor)
{
    this->rectangle.setFillColor(buttonColor);
}

TextButton::TextButton(sf::Color buttonColor, sf::Vector2f position, sf::Vector2f size, sf::Text text):
    Button(buttonColor, position, size)
{
    this->text = text;
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(this->rectangle.getPosition());
}

void TextButton::changeText(std::string text)
{
    this->text.setString(text);
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(this->rectangle.getPosition());
}

void TextButton::changeText(sf::Text text)
{
    this->text = text;
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);
    this->text.setPosition(this->rectangle.getPosition());
}

void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Button::draw(target, states);
    target.draw(text);
}

Slider::Slider(sf::Color buttonColor, sf::Vector2f position, sf::Vector2f size, float max, sf::Color pointColor, float pointSize, float pointPosition):
    Button(buttonColor, position, size)
{
    point.setFillColor(pointColor);
    point.setRadius(pointSize);
    point.setOrigin(pointSize, pointSize);

    point.setPosition(rectangle.getGlobalBounds().left + (pointPosition / max) * rectangle.getGlobalBounds().width, rectangle.getPosition().y);
    this->pointPosition = ((point.getPosition().x - rectangle.getGlobalBounds().left) / rectangle.getGlobalBounds().width) * max;

    this->max = max;
}

Slider::~Slider()
{
}

void Slider::update(sf::Window& win)
{
    Button::update(win);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && hover())
    {
        pointPosition = ((mousex - rectangle.getGlobalBounds().left) / rectangle.getGlobalBounds().width) * max;
        point.setPosition(mousex, rectangle.getPosition().y);
    }
}

float Slider::getCurrentPoint()
{
    return pointPosition;
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    Button::draw(target, states);
    target.draw(point);
}
