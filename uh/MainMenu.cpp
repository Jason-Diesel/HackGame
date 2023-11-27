#include "MainMenu.h"

MainMenu::MainMenu():
	wnd(sf::VideoMode(800, 800), "")
{

}

MainMenu::~MainMenu()
{
	wnd.close();
	//TODO : Delete shit
	delete start;
	delete exit;

	delete TurnOnOffMusic;
	delete Easy;
	delete Medium;
	delete Hard;

	delete musicVolumeSlider;
	delete masterVolumeSlider;
}

void MainMenu::init()
{
	Title.setCharacterSize(100);
	Title.setFont(rm->getFont("../Fonts/Roboto-Black.ttf"));
	Title.setFillColor(sf::Color(200,30,30));
	Title.setString("Fake Virus");
	Title.setPosition(400 - (Title.getGlobalBounds().width / 2), 100);

	sf::Text text;
	text.setFont(rm->getFont("../Fonts/Roboto-Black.ttf"));
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setString("Start");
	start = new TextButton(sf::Color(200, 30, 30), sf::Vector2f(150,300), sf::Vector2f(200, 50), text);

	text.setString("Exit");
	exit = new TextButton(sf::Color(200, 30, 30), sf::Vector2f(150, 700), sf::Vector2f(200, 50), text);

	text.setString("EASY");
	Easy = new TextButton(sf::Color(50,50,50), sf::Vector2f(100, 400), sf::Vector2f(100, 50), text);
	text.setString("MEDIUM");
	Medium = new TextButton(sf::Color(50,50,50), sf::Vector2f(225, 400), sf::Vector2f(100, 50), text);
	text.setString("HARD");
	Hard = new TextButton(sf::Color(50,50,50), sf::Vector2f(350, 400), sf::Vector2f(100, 50), text);

	switch (Settings::getInstance().difficulty)
	{
	case Difficulty::EASY:
		Easy->changeColor(sf::Color(0,150,0));
		break;
	case Difficulty::MEDIUM:
		Medium->changeColor(sf::Color(0,150,0));
		break;
	case Difficulty::HARD:
		Hard->changeColor(sf::Color(0,150,0));
		break;
	default:
		break;
	}

	if (Settings::getInstance().music)
	{
		text.setString("Turn OFF music");
	}
	else
	{
		text.setString("Turn ON music");
	}
	TurnOnOffMusic = new TextButton(sf::Color(200, 30, 30), sf::Vector2f(150, 500), sf::Vector2f(200, 50), text);

	musicVolumeSlider = new Slider(sf::Color(50, 50, 50), sf::Vector2f(150, 625), sf::Vector2f(200, 10), 100, sf::Color::Blue, 10, Settings::getInstance().musicVolume);
	musicVolumeText = text;
	musicVolumeText.setString("music Volume : " + std::to_string(musicVolumeSlider->getCurrentPoint()));
	musicVolumeText.setPosition(sf::Vector2f(50, 575));
	
	masterVolumeSlider = new Slider(sf::Color(50, 50, 50), sf::Vector2f(400, 625), sf::Vector2f(200, 10), 100, sf::Color::Blue, 10, Settings::getInstance().masterVolume);
	masterVolumeText = text;
	masterVolumeText.setString("master Volume : " + std::to_string(musicVolumeSlider->getCurrentPoint()));
	masterVolumeText.setPosition(sf::Vector2f(300, 575));
}

SceneUpdate MainMenu::Update(float dt)
{
	start->update(wnd);
	exit->update(wnd);
	TurnOnOffMusic->update(wnd);
	Easy->update(wnd);
	Medium->update(wnd);
	Hard->update(wnd);
	musicVolumeSlider->update(wnd);
	masterVolumeSlider->update(wnd);

	if(start->clicked())
	{
		Settings::getInstance().saveSettings();
		return SceneUpdate::GameScene;//TODO : change to tutorial Scene?
	}

	if(Easy->clicked())
	{
		Settings::getInstance().difficulty = Difficulty::EASY;
		Easy->changeColor(sf::Color(0,150,0));
		Medium->changeColor(sf::Color(50,50,50));
		Hard->changeColor(sf::Color(50,50,50));
	}
	if(Medium->clicked())
	{
		Settings::getInstance().difficulty = Difficulty::MEDIUM;
		Easy->changeColor(sf::Color(50,50,50));
		Medium->changeColor(sf::Color(0,150,0));
		Hard->changeColor(sf::Color(50,50,50));
	}
	if(Hard->clicked())
	{
		Settings::getInstance().difficulty = Difficulty::HARD;
		Easy->changeColor(sf::Color(50,50,50));
		Medium->changeColor(sf::Color(50,50,50));
		Hard->changeColor(sf::Color(0,150,0));
	}

	if (TurnOnOffMusic->clicked())
	{
		Settings::getInstance().music = !Settings::getInstance().music;
		if (Settings::getInstance().music)
		{
			TurnOnOffMusic->changeText("Turn OFF music");
		}
		else
		{
			TurnOnOffMusic->changeText("Turn ON music");
		}
	}

	if (exit->clicked())
	{
		Settings::getInstance().saveSettings();
		return SceneUpdate::QUIT;
	}

	musicVolumeText.setString("music Volume : " + std::to_string((int)musicVolumeSlider->getCurrentPoint()));
	Settings::getInstance().musicVolume = musicVolumeSlider->getCurrentPoint();
	masterVolumeText.setString("master Volume : " + std::to_string((int)masterVolumeSlider->getCurrentPoint()));
	Settings::getInstance().masterVolume = masterVolumeSlider->getCurrentPoint();

	sf::Event event;
	while (wnd.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			return SceneUpdate::QUIT;
		}
	}

	return SceneUpdate();
}

void MainMenu::Render()
{
	wnd.clear();

	wnd.draw(Title);

	wnd.draw(*start);
	wnd.draw(*exit);
	wnd.draw(*TurnOnOffMusic);

	wnd.draw(*Easy);
	wnd.draw(*Medium);
	wnd.draw(*Hard);

	wnd.draw(musicVolumeText);
	wnd.draw(*musicVolumeSlider);

	wnd.draw(masterVolumeText);
	wnd.draw(*masterVolumeSlider);

	wnd.display();
}
