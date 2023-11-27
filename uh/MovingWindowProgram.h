#pragma once
#include "VirtualPrograms.h"
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

class MovementWindowProgram : public VirtualPrograms
{
public:
    MovementWindowProgram(const std::string& windowName);
    void init();
    VirtualProgramReturn update(float dt);
    void draw();
private:
    void mouseMovement(float dt);
    void getNewGoal();
    void rotateTheMouse(const sf::Vector2f& dir);
    sf::Vector2f theMousePos();//not the mouse you click but the mouse

    float speed;
    sf::Vector2f WindowPos;
    sf::Sprite TheMouse;

    float walkingToWardsTime = 0;
    float maxWalkingToWardsTime = 2;
    sf::Vector2f goal;

};