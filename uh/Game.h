#pragma once
#pragma comment(lib, "opengl32.lib")

#include <iostream>
#include "ResourceManager.h"
#include "Scene.h"
#include <random>

//PROGRAMS
#include "adProgram.h"
#include "CryptateProgram.h"
#include "MovingProgram.h"
#include "FileCheckerChangerProgram.h"
#include "MouseMovementProgram.h"
#include "MovingWindowProgram.h"



class Game : public Scene{
private:
	int nrOfPrograms;
	float gameplayTime;
	std::vector<VirtualPrograms*> programs;
	void createProgram();
public:
	Game();
	virtual ~Game();
	void init();
	SceneUpdate Update(float dt);
	void Render();
	void HandleEvents();
	float getGamePlayTime();
private:
	sf::Music music;
};