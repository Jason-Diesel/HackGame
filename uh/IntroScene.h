#pragma once
#include "Scene.h"
#include "Button.h"

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

class IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();
	void init();
	SceneUpdate Update(float dt); 
	void Render();
private:
	//Objects
	sf::Sprite woman;
	sf::Sprite background;

	sf::Sprite discord;
	Button answear;
	Button decline;

	sf::RenderWindow win;
	sf::Music discordMusic;
	sf::Sound DiscordRant1;
	sf::Sound DiscordRant2;

	//events
	bool in_discord;
	bool pressAnswear;
};