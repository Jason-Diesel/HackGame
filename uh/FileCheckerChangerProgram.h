#pragma once
#include "VirtualPrograms.h"
#include <fstream>
#include "MatrixRainDrop.h"
#include <iostream>

class FileCheckerChangerProgram : public VirtualPrograms
{
public:
	FileCheckerChangerProgram(const std::string& windowName);
	virtual ~FileCheckerChangerProgram();
	void init();
	VirtualProgramReturn update(float dt);
	void draw();
	void handleEvents();
private:
	sf::Text timeLeftText;
	
	const int nrOfDrops = 20;
	std::vector<MatrixRainDrop> drops;

private:
	std::ofstream outfileStreamer;
	std::ifstream infileStreamer;
	bool failSafe = false;//a fail safe
	void writeToFile();
	uint32_t thisID;

	const int maxNumberOfWords = 130;
	const int minNumberOfWords = 30;
	int fileSize;
	int getFileSize();

	//checker
	float currentTimeToCheck = 0;
	float maxTimeToCheck = 3.0f;
	
	float maxTimeToChangeFile = 60;

	bool checkFile();
};
