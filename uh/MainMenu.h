#pragma once
#include "Scene.h"
#include "Button.h"

class MainMenu : public Scene
{
public:
	MainMenu();
	~MainMenu();
	void init();
	SceneUpdate Update(float dt);
	void Render();
private:
	sf::Text Title;

	TextButton* start;
	TextButton* exit;

	//settings
	TextButton* TurnOnOffMusic;
	TextButton* Easy;
	TextButton* Medium;
	TextButton* Hard;

	sf::Text musicVolumeText;
	Slider* musicVolumeSlider;

	sf::Text masterVolumeText;
	Slider* masterVolumeSlider;

	sf::RenderWindow wnd;
};