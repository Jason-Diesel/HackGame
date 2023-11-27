#pragma once
#include <fstream>

enum Difficulty
{
	EASY = 1,
	MEDIUM = 2,
	HARD = 3,
};

class Settings
{
public:
	static Settings& getInstance() {
        static Settings instance;
        return instance;
    }
	void loadDefaultSettings();
	void saveSettings();

public: // I do not have the ork to create getters and setters

	const std::string filePath = "../data/settings.txt";
	int nrOfPrograms;//also a type of difficulty
	Difficulty difficulty;//easy 1 program, medium 2 programs, hard 3 programs at a time;

	bool music;
	float musicVolume;
	float masterVolume;

private:
	Settings()
	{
		loadDefaultSettings();
	}
	Settings(const Settings&) = delete;
    Settings& operator=(const Settings&) = delete;
};