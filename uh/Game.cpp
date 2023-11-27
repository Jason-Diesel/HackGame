#include "Game.h"

void Game::createProgram()
{
	VirtualPrograms* newProgram;
	int programType = rand() % 6;
	
	switch(programType)
	{
	case 0:
		newProgram = new adProgram("Fake Virus AD", sf::Vector2i(0,0), sf::Vector2u(550, 400));
		break;
	case 1:
		newProgram = new CryptateProgram("Fake Virus Cryptate");
		break;
	case 2:
		newProgram = new FileCheckerChangerProgram("Fake Virus Check_File");
		break;
	case 3:
		newProgram = new MouseMovementProgram("Fake Virus Mouse Movement");
		break;
	case 4:
		newProgram = new MovingProgram("Fake Virus Window Movement");
		break;
	case 5:
		newProgram = new MovementWindowProgram("Mouse");
		break;
	}

	programs.push_back(newProgram);
	newProgram->setRandomPosition();
	newProgram->addResourceManager(rm);
	newProgram->init();
}

Game::Game():
	gameplayTime(0)
{	
	srand((unsigned)time(NULL));
}

Game::~Game()
{
	music.stop();
	for(int i = 0; i < programs.size(); i++)
	{
		delete programs[i];
	}
}

void Game::init()
{
	for(int i = 0; i < Settings::getInstance().difficulty; i++)
	{
		createProgram();
	}
	nrOfPrograms = Settings::getInstance().nrOfPrograms;

	if(Settings::getInstance().music)
	{
		if (!music.openFromFile("../Audio/Darksynth_Cyberpunk_Industrial-Lose_Control_by_Karl_Casey.ogg"))
		{
		    std::cout << "cannot open music file" << std::endl;
		}
		music.setVolume(Settings::getInstance().musicVolume);
		music.play();
	}
}

SceneUpdate Game::Update(float dt)
{
	if (Settings::getInstance().music && music.getPlayingOffset().asSeconds() >= 191.982f)
    {
        music.setPlayingOffset(sf::seconds(38.4f));
    }
	gameplayTime += dt;
	for (int i = 0; i < programs.size(); i++)
	{
		programs[i]->handleEvents();
		switch(programs[i]->update(dt))
		{
		case VirtualProgramReturn::Exit:
			delete programs[i];
			programs.erase(programs.begin() + i);
			nrOfPrograms--;
			if(nrOfPrograms > 0)
			{
				createProgram();
			}
			else if(programs.size() == 0){
				return SceneUpdate::WinningScene;
			}
			break;
		case VirtualProgramReturn::Hacked:
			return SceneUpdate::GameOverScene;
			break;
		}
	}
	return SceneUpdate::Continue;
}

void Game::Render()
{
	for (int i = 0; i < programs.size(); i++)
	{
		programs[i]->draw();
	}
}

void Game::HandleEvents()
{
}

float Game::getGamePlayTime()
{
	return gameplayTime;
}
