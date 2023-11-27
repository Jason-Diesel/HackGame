#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	sf::Font& getFont(const std::string& fontPath);
	sf::Sprite getSprite(const std::string& filePath);
	sf::SoundBuffer& getSoundBuffer(const std::string& filePath);
private:
	void createSprite(const std::string& filePath);
	std::map<std::string, sf::SoundBuffer> soundBuffers;
	std::map<std::string, sf::Font> fonts;
	std::map<std::string, sf::Sprite> sprites;
	std::vector<sf::Texture*> textures;
};