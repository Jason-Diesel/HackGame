#pragma once
#include "ResourceManager.h"
#include "Settings.h"
#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")


enum class SceneUpdate{
Continue,
GameScene,
GameOverScene,
MenuScene,
WinningScene,
QUIT
};

class Scene
{
public:
	Scene();
	virtual ~Scene();
	virtual void init();
	virtual SceneUpdate Update(float dt);
	virtual void Render();
	void setResourceManager(ResourceManager* rm);
protected:
	ResourceManager* rm;
};