#pragma once
#include "Scene.h"

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

class WinningScene : public Scene
{
public:
	WinningScene();
	~WinningScene();
	void init();
	SceneUpdate Update(float dt);
	void Render();
	void getTime(float time);
private:
	sf::Music youDidItSound;
	sf::Sprite woman;
	sf::Sprite background;

	sf::Text pressEnter;
	sf::Text timeText;
	sf::Text backpressEnter;
	sf::Text backtimeText;
	float time;

	sf::RenderWindow win;
};