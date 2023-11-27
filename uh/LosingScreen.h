#include "Scene.h"

class LosingScreen : public Scene
{
public:
	LosingScreen();
	virtual ~LosingScreen();
	void init();
	virtual SceneUpdate Update(float dt);
	virtual void Render();
private:
	float time;

	sf::RenderWindow win;
	sf::Sound sound;
	sf::Sprite Skull;
	sf::Text hackedText;
};
