#include "MouseMovementProgram.h"

MouseMovementProgram::MouseMovementProgram(const std::string& windowName) :
    VirtualPrograms(windowName, sf::Vector2i(0, 0), sf::Vector2u(300, 600))
{
   
}

void MouseMovementProgram::init()
{
    text.setFont(rm->getFont("../Fonts/Roboto-Black.ttf"));
    text.setString("Not a virus");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(110, 200);
}

VirtualProgramReturn MouseMovementProgram::update(float dt)
{
    nextUpdate += dt;
    if (nextUpdate > maxTimeUntilUpdate)
    {
        nextUpdate = 0;
        sf::Mouse::setPosition(sf::Vector2i(sf::Mouse::getPosition().x + 1, sf::Mouse::getPosition().y + 1));
    }
    if (this->deletedWindow)
    {
        return VirtualProgramReturn::Exit;
    }

    return VirtualProgramReturn::Continue;
}

void MouseMovementProgram::draw()
{
    window.clear();
    window.draw(text);
    window.display();
}
