#include "IntroScene.h"

IntroScene::IntroScene():
    answear(sf::Color(0,255,0,100), sf::Vector2f(335,271), sf::Vector2f(60,60)),
    decline(sf::Color(255,0,0,100), sf::Vector2f(250,271), sf::Vector2f(60,60)),
    win(sf::VideoMode(780, 440), "Fake Discord", sf::Style::None)
{
    in_discord = true;
    pressAnswear = false;

    DWM_BLURBEHIND bb = { 0 };
    bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;;
    bb.fEnable = true;
    bb.fTransitionOnMaximized = false;
    bb.hRgnBlur = CreateRectRgn(-1, -1, 0, 0);
    DwmEnableBlurBehindWindow(win.getSystemHandle(), &bb);
}

IntroScene::~IntroScene()
{
}

void IntroScene::init()
{
    discord = rm->getSprite("../Textures/discordcall.png");
    discord.setScale(0.75, 0.75);
    woman = rm->getSprite("../Textures/Woman1.png");
    woman.setScale(20.f, 20.f);
    woman.setPosition(sf::Vector2f(17, 40));
    background = rm->getSprite("../Textures/profileBorder.png");

    discordMusic.openFromFile("../Audio/DiscordIncomingCallSound.ogg");
    discordMusic.setLoop(true);
    discordMusic.setVolume(Settings::getInstance().masterVolume);
    discordMusic.play();

    DiscordRant1.setBuffer(rm->getSoundBuffer("../Audio/TestAudio/didYouJustTrrToHangUpOnMe.ogg"));
    DiscordRant2.setBuffer(rm->getSoundBuffer("../Audio/TestAudio/eyYourComputerJustGotHacked.ogg"));
    DiscordRant1.setVolume(Settings::getInstance().masterVolume);
    DiscordRant2.setVolume(Settings::getInstance().masterVolume);
}

SceneUpdate IntroScene::Update(float dt)
{
    if (in_discord)
    {
        answear.update(win);
        decline.update(win);
        if (answear.clicked())
        {
            discordMusic.stop();
            in_discord = false;
            pressAnswear = true;
        }
        else if (decline.clicked()) 
        {
            discordMusic.stop();
            in_discord = false;
            DiscordRant1.play();
        }
    }
    else 
    {
        if (pressAnswear)
        {
            static bool once = false;
            if (!once)
            {
                once = true;
                DiscordRant2.play();
            }
            if (DiscordRant2.getStatus() != sf::Sound::Playing)
            {
                return SceneUpdate::MenuScene;
            }
        }
        else
        {
            if (DiscordRant1.getStatus() != sf::Sound::Playing)
            {
                pressAnswear = true;
            }
        }
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

void IntroScene::Render()
{
    win.clear(sf::Color(0,0,0,0));

    if (in_discord)
    {
        win.draw(discord);
    }
    else
    {
        win.draw(woman);
        win.draw(background);
    }

    win.display();
}
