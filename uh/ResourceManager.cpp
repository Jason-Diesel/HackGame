#include "ResourceManager.h"
#include <iostream>
#include <Windows.h>

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    for (int i = 0; i < textures.size(); i++)
    {
        delete textures[i];
    }
}

sf::Font& ResourceManager::getFont(const std::string& fontPath)
{
    if(fonts.find(fontPath) == fonts.end())
    {
        sf::Font font;
        if(!font.loadFromFile(fontPath))
        {
            MessageBox(nullptr, L"Cannot load font", L"Error loading", MB_ICONERROR);
            exit(-1);
        }
        fonts.insert(std::pair<std::string, sf::Font>(fontPath, font));
    }
    return fonts[fontPath];
}

sf::Sprite ResourceManager::getSprite(const std::string& filePath)
{
    if (sprites.find(filePath) == sprites.end())
    {
        createSprite(filePath);
    }
    return sprites[filePath];
}

sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& filePath)
{
    if (soundBuffers.find(filePath) == soundBuffers.end())
    {
        sf::SoundBuffer sb;
        sb.loadFromFile(filePath);
        soundBuffers.insert(std::pair<std::string, sf::SoundBuffer>(filePath, sb));
    }
    return soundBuffers[filePath];
}

void ResourceManager::createSprite(const std::string& filePath)
{
    sf::Texture* tex = new sf::Texture();
    if(!tex->loadFromFile(filePath))
    {
        MessageBox(nullptr, L"Cannot load sprite", L"Error loading", MB_ICONERROR);
        exit(-1);
    }
    textures.push_back(tex);
    sf::Sprite s = sf::Sprite(*textures.back());

    sprites.insert(std::pair<std::string, sf::Sprite&>(filePath, s));
}
