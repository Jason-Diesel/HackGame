#include "LosingScreen.h"

LosingScreen::LosingScreen()
    :win(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height - 1), "", sf::Style::None)
{
    win.setPosition(sf::Vector2i(0, 0));
    
    DWM_BLURBEHIND bb = { 0 };
    bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;;
    bb.fEnable = true;
    bb.fTransitionOnMaximized = false;
    bb.hRgnBlur = CreateRectRgn(-1, -1, 0, 0);
    DwmEnableBlurBehindWindow(win.getSystemHandle(), &bb);
}

LosingScreen::~LosingScreen()
{
    win.close();
}

void LosingScreen::init()
{
    Skull = rm->getSprite("../Textures/deathSkull.png");
    Skull.setPosition(sf::VideoMode::getDesktopMode().width/2 - 175, sf::VideoMode::getDesktopMode().height/2 - 448);
    
    hackedText.setFont(rm->getFont("../Fonts/Roboto-Black.ttf"));
    hackedText.setString("HACKED");
    hackedText.setCharacterSize(69);
    hackedText.setFillColor(sf::Color(200, 0, 0, 255));

    hackedText.setPosition(sf::VideoMode::getDesktopMode().width / 2 - (hackedText.getGlobalBounds().width / 2),
        sf::VideoMode::getDesktopMode().height / 2);

    sound.setBuffer(rm->getSoundBuffer("../Audio/wannymanny__evil-laugh-muahaha.wav"));
    sound.setVolume(Settings::getInstance().masterVolume);
    sound.play();
    time = 9;
}

SceneUpdate LosingScreen::Update(float dt)
{
    time -= dt;
    if (time < 0)
    {
        return SceneUpdate::MenuScene;
    }
    sf::Event event;
	while (win.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
            return SceneUpdate::QUIT;
			win.close();
		}
	}

    return SceneUpdate::Continue;
}

void LosingScreen::Render()
{
    win.clear(sf::Color(0, 0, 0, 0));

    win.draw(Skull);
    win.draw(hackedText);

    win.display();
}

