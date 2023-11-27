#include "Settings.h"
#include <string>

void Settings::loadDefaultSettings()
{
	struct stat buffer;
	if (stat(filePath.c_str(), &buffer) == 0)
	{
		std::ifstream file;
		file.open(filePath.c_str());
		if (!file.is_open())
		{
			printf("couldn't open file\n");
			return;
		}
		int dif;
		file >> nrOfPrograms;
		file >> dif; this->difficulty = (Difficulty)dif;
		file >> music;
		file >> musicVolume;
		file >> masterVolume;
		
		file.close();
	}
	else
	{
		this->nrOfPrograms = 10;
		this->difficulty = Difficulty::EASY;

		this->music = true;
		this->musicVolume = 1;
		this->masterVolume = 1;
		saveSettings();
	}
}

void Settings::saveSettings()
{
	std::ofstream file;
	file.open(filePath.c_str());
	if (!file.is_open())
	{
		printf("couldn't open file\n");
		return;
	}
	file << nrOfPrograms << std::endl;
	file << (int)difficulty << std::endl;
	file << music << std::endl;
	file << musicVolume << std::endl;
	file << masterVolume << std::endl;
	file.close();
}
