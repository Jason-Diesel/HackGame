#include "MovingWindowProgram.h"
#include <iostream>

float lenght(sf::Vector2f points)
{
    return sqrt(points.x * points.x + points.y * points.y);
}

sf::Vector2f& normalizeVector(sf::Vector2f& vector)
{
    vector = vector/ (lenght(vector) + 0.0001f);//just make sure we never divide with 0
    return vector;
}

MovementWindowProgram::MovementWindowProgram(const std::string& windowName):
    VirtualPrograms(windowName, sf::Vector2i(0,0), sf::Vector2u(200,200))
{
    speed = 500;

    //Make style to none
	DWORD style = ::GetWindowLong(window.getSystemHandle(), GWL_STYLE);
	style &= ~WS_OVERLAPPEDWINDOW;
	style |= WS_POPUP;
	::SetWindowLong(window.getSystemHandle(), GWL_STYLE, style);

    DWM_BLURBEHIND bb = { 0 };
    bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;;
    bb.fEnable = true;
    bb.fTransitionOnMaximized = false;
    bb.hRgnBlur = CreateRectRgn(-1, -1, 0, 0);
    DwmEnableBlurBehindWindow(window.getSystemHandle(), &bb);
}

void MovementWindowProgram::init()
{
    TheMouse = rm->getSprite("../Textures/Mouse.png");
    TheMouse.setOrigin(
        TheMouse.getGlobalBounds().width / 2,
        TheMouse.getGlobalBounds().height / 2
    );
    TheMouse.setScale(0.3f, 0.3f);
    TheMouse.setPosition(100, 100);
    WindowPos = sf::Vector2f(window.getPosition());
}

VirtualProgramReturn MovementWindowProgram::update(float dt)
{
    mouseMovement(dt);

    if(window.hasFocus() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        if(pos.x > 0 && pos.x < 200 && pos.y > 0 && pos.y < 200)
        {
            return VirtualProgramReturn::Exit;
        }
    }

    return VirtualProgramReturn::Continue;
}

void MovementWindowProgram::draw()
{
    window.clear(sf::Color(0,0,0,0));

    window.draw(TheMouse);

    window.display();
}

void MovementWindowProgram::mouseMovement(float dt) 
{
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition());
    if (window.getPosition().x > (int)sf::VideoMode::getDesktopMode().width - 210)
    {
        WindowPos.x = 1;
    }
    else if (window.getPosition().y > (int)sf::VideoMode::getDesktopMode().height - 210)
    {
        WindowPos.y = 1;
    }
    else if (window.getPosition().x < 1)
    {
        WindowPos.x = (float)sf::VideoMode::getDesktopMode().width - 210.f;
    }
    else if (window.getPosition().y < 1)
    {
        WindowPos.y = (float)sf::VideoMode::getDesktopMode().height - 300.f;
    }



    //if mouse sees mouse run away
    if (lenght(mousePos - theMousePos()) < 400)
    {
        //run away
        sf::Vector2f dir = theMousePos() - mousePos;
        rotateTheMouse(dir);
        WindowPos += normalizeVector(dir) * dt * speed;
        walkingToWardsTime = maxWalkingToWardsTime;
    }
    else //walk aimesly
    {
        walkingToWardsTime += dt;
        if(walkingToWardsTime > maxWalkingToWardsTime)
        {
            walkingToWardsTime = 0;
            getNewGoal();
        }
        
        sf::Vector2f dir = goal - theMousePos();
            
        rotateTheMouse(dir);

        WindowPos += normalizeVector(dir) * dt * (speed/5);
    }

    window.setPosition(sf::Vector2i(WindowPos));
}

void MovementWindowProgram::getNewGoal()
{
    goal = sf::Vector2f(
        (float)(rand() % ((int)sf::VideoMode::getDesktopMode().width - 450)) + 225.f,
        (float)(rand() % ((int)sf::VideoMode::getDesktopMode().height - 450)) + 225.f
    );
}

void MovementWindowProgram::rotateTheMouse(const sf::Vector2f& dir)
{
    float rotation = (atan2(dir.y, dir.x)) * 180.f / 3.14159265f;
    TheMouse.setRotation(rotation + 90.f);
}

sf::Vector2f MovementWindowProgram::theMousePos()
{
    return sf::Vector2f(window.getPosition() + sf::Vector2i(150,150));
}