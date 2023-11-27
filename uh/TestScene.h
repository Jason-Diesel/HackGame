#pragma once
#include "Scene.h"

class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();
	void init();
	SceneUpdate Update(float dt);
	void Render();
private:
	sf::SoundBuffer buffer;
	sf::Sound begining;
	sf::Music music;
};