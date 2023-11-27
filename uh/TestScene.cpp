#include "TestScene.h"
#include <iostream>

TestScene::TestScene()
{
    buffer.loadFromFile("../Audio/wannymanny__evil-laugh-muahaha.wav");
    begining.setBuffer(buffer);

    if (!music.openFromFile("../Audio/Darksynth_Cyberpunk_Industrial-Lose_Control_by_Karl_Casey.ogg"))
    {
        std::cout << "cannot open music file" << std::endl;
    }
    music.setLoop(true);
}

TestScene::~TestScene()
{
}

void TestScene::init()
{
    music.play();
    begining.setVolume(100);
    //begining.play();
}

SceneUpdate TestScene::Update(float dt)
{
    if (music.getPlayingOffset().asSeconds() >= 191.982f)
    {
        music.setPlayingOffset(sf::seconds(38.4f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        std::cout << "set music offset" << std::endl;
        music.setPlayingOffset(sf::seconds(187.982f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        printf("music position %f \n", music.getPlayingOffset().asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        return SceneUpdate::QUIT;
    }
    return SceneUpdate::Continue;
}

void TestScene::Render()
{
}
