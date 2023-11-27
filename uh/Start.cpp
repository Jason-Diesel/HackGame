//Scenes
#include "Game.h"
#include "LosingScreen.h"
#include "MainMenu.h"
#include "TestScene.h"
#include "IntroScene.h"
#include "WinningScene.h"

#include "DeltaTime.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand((unsigned int)time(0));
	DeltaTime dt;
	ResourceManager* rm;
	
	
	//Scene* game = new TestScene();
	//Scene* game = new MainMenu();
	Scene* game = new IntroScene();
	rm = new ResourceManager();
	game->setResourceManager(rm);
	game->init();
	float tTime;
	
	SceneUpdate quit = SceneUpdate::Continue;
	while (quit != SceneUpdate::QUIT) {
		quit = game->Update((float)dt.dt());
		game->Render();
		dt.restartClock();
		switch (quit)
		{
		case SceneUpdate::GameScene:
			delete game;
			game = new Game();
			game->setResourceManager(rm);
			game->init();
			break;
		case SceneUpdate::GameOverScene:
			delete game;
			game = new LosingScreen();
			game->setResourceManager(rm);
			game->init();
			break;
		case SceneUpdate::MenuScene:
			delete game;
			game = new MainMenu();
			game->setResourceManager(rm);
			game->init();
			break;
		case SceneUpdate::WinningScene:
			tTime = ((Game*)game)->getGamePlayTime();
			delete game;
			game = new WinningScene();
			game->setResourceManager(rm);
			((WinningScene*)game)->getTime(tTime);
			game->init();
			break;
		default:
			break;
		}
	}
	
	delete game;
	delete rm;
	return 0;
}
