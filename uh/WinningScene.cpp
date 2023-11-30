#include "WinningScene.h"

WinningScene::WinningScene():
	win(sf::VideoMode(800,600), "winning", sf::Style::None)
{
    DWM_BLURBEHIND bb = { 0 };
    bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;;
    bb.fEnable = true;
    bb.fTransitionOnMaximized = false;
    bb.hRgnBlur = CreateRectRgn(-1, -1, 0, 0);
    DwmEnableBlurBehindWindow(win.getSystemHandle(), &bb);
}

WinningScene::~WinningScene()
{
}

void WinningScene::init()
{
    woman = rm->getSprite("../Textures/Woman1.png");
    woman.setScale(20.f, 20.f);
    woman.setPosition(sf::Vector2f(17, 40));
    background = rm->getSprite("../Textures/profileBorder.png");

    youDidItSound.openFromFile("../Audio/LiaAudio/Winning.ogg");//TODO : change this to lia
    youDidItSound.setVolume(Settings::getInstance().masterVolume);
    youDidItSound.setLoop(false);
    youDidItSound.play();

    pressEnter.setFont(rm->getFont("../Fonts/Roboto-Black.ttf"));
    pressEnter.setCharacterSize(24);
    pressEnter.setFillColor(sf::Color::White);
    pressEnter.setPosition(0,400);
    timeText = pressEnter;
    timeText.setCharacterSize(50);
    pressEnter.setString("Good jobb! press enter to go back to menu");
    timeText.setString("Time: " + std::to_string(time));
    timeText.setPosition(0, 350);

    backpressEnter = pressEnter;
    backpressEnter.setScale(1.f, 1.1);
    backpressEnter.move(3, 0);
    backpressEnter.setFillColor(sf::Color::Black);
    backtimeText = timeText;
    backtimeText.move(3, 0);
    backtimeText.setScale(1.f, 1.1);
    backtimeText.setFillColor(sf::Color::Black);
}

SceneUpdate WinningScene::Update(float dt)
{
    sf::Event event;
	while (win.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
            return SceneUpdate::QUIT;
			win.close();
		}
	}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        return SceneUpdate::MenuScene;
    }
    return SceneUpdate::Continue;
}

void WinningScene::Render()
{
    win.clear(sf::Color(0, 0, 0, 0));

    win.draw(woman);
    win.draw(background);
    win.draw(backpressEnter);
    win.draw(backtimeText);
    win.draw(pressEnter);
    win.draw(timeText);

    win.display();
}

void WinningScene::getTime(float time)
{
    this->time = time;
}
