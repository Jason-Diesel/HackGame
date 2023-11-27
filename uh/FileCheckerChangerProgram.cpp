#include "FileCheckerChangerProgram.h"

//static const std::string words[] = {
//	"penis",
//	"snopp\n",
//	"cock",
//	"melons",
//	"badokadongs\n",
//	"cake",
//	"susage",
//	"im Kinda hungry for pizza\n",
//	"LoremIpsum"
//};

static const std::string words[] = {
	"01100101 01100001 01110011 01110100 01100101 01110010 00100000 01100101 01100111 01100111",
	"	int ret;\nret = crypto_register_alg(&alg);\n	if (ret)\n		return ret;\n	ret = crypto_register_scomp(&scomp);\n	if (ret){ \n		crypto_unregister_alg(&alg);\n		return ret;\n	}",
	"MATRIX4X4",
	"melons",
	"74 97 115 111 110 68 105 101 115 101 108 \n",
	"sf::RenderWindow window(sf::VideoMode(800, 600), 'SFML window');",
	"susage",
	"im Kinda hungry for pizza\n",
	"orem ipsum dolor sit amet, consectetur adipiscing elit."
};

#define wordsLenght 9

FileCheckerChangerProgram::FileCheckerChangerProgram(const std::string& windowName):
	VirtualPrograms(windowName, sf::Vector2i(0,0), sf::Vector2u(300,200))
{
	writeToFile();
}

FileCheckerChangerProgram::~FileCheckerChangerProgram()
{
	std::string fileName = "../FileCheckerFakeVirus_" + std::to_string(thisID) + "_.txt";

	struct stat buffer;
	if (stat(fileName.c_str(), &buffer) == 0)
	{
		std::remove(fileName.c_str());
	}
}

void FileCheckerChangerProgram::init()
{
	timeLeftText.setFont(rm->getFont("../Fonts/Roboto-Black.ttf"));
	timeLeftText.setPosition(100, 75);
	timeLeftText.setCharacterSize(24);
	timeLeftText.setFillColor(sf::Color::Green);
	for (int i = 0; i < nrOfDrops; i++)
	{
		drops.push_back(MatrixRainDrop(sf::Vector2f(300, 200), rm->getFont("../Fonts/Roboto-Black.ttf")));
	}
}

VirtualProgramReturn FileCheckerChangerProgram::update(float dt)
{
	if(failSafe){return VirtualProgramReturn::Exit;}//incase we couldn't create a file

	for (int i = 0; i < nrOfDrops; i++)
	{
		drops[i].update(dt);
	}
	currentTimeToCheck += dt;
	maxTimeToChangeFile -= dt;
	timeLeftText.setString(std::to_string(maxTimeToChangeFile));
	//we do not wanna check the file all the time
	if(currentTimeToCheck > maxTimeToCheck)
	{
		currentTimeToCheck = 0;
		if(checkFile())
		{
			return VirtualProgramReturn::Exit;
		}
	}

	if (maxTimeToChangeFile < 0)
	{
		return VirtualProgramReturn::Hacked;
	}

	return VirtualProgramReturn::Continue;
}

void FileCheckerChangerProgram::draw()
{
	window.clear();

	window.draw(timeLeftText);
	for (int i = 0; i < nrOfDrops; i++)
	{
		window.draw(drops[i]);
	}
	

	window.display();
}

void FileCheckerChangerProgram::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		
	}
}

void FileCheckerChangerProgram::writeToFile()
{
	int nrOfWords = (rand() % (maxNumberOfWords - minNumberOfWords)) + minNumberOfWords;//minimum of 30 words max 130
	int SpecialWordIndex = rand() % nrOfWords;
	//do we need to create some extra checks here?

	static uint32_t id = 0;
	id++;
	thisID = id;
	fileSize = 0;

	outfileStreamer.open("../FileCheckerFakeVirus_" + std::to_string(thisID) + "_.txt");
	if(!outfileStreamer.is_open())
	{
		failSafe = true;
		return;
	}

	for(int i = 0; i < nrOfWords; i++)
	{
		if(i == SpecialWordIndex)
		{
			outfileStreamer << " EULA = FALSE ";
		}
		else
		{
			std::string writeString = words[rand() % wordsLenght];
			outfileStreamer << writeString;
		}
	}
	outfileStreamer << "\n";
	outfileStreamer.close();

	fileSize = getFileSize();
}

int FileCheckerChangerProgram::getFileSize()
{
	std::string line;
	int size = 0;
	infileStreamer.open("../FileCheckerFakeVirus_" + std::to_string(thisID) + "_.txt");
	if (infileStreamer.is_open())
	{
		while (std::getline(infileStreamer, line))
		{
			size += (int)line.size();
		}
		infileStreamer.close();
	}
	return size;
}

bool FileCheckerChangerProgram::checkFile()
{
	std::string line;
	bool foundTrue = false;
	int size = 0;
	infileStreamer.open("../FileCheckerFakeVirus_" + std::to_string(thisID) + "_.txt");
	if (infileStreamer.is_open())
	{
		while (std::getline(infileStreamer, line))
		{
			if(line.find("EULA = FALSE") != std::string::npos)
			{
				infileStreamer.close();
				return false;
			}
			else if(line.find("EULA = TRUE") != std::string::npos)
			{
				foundTrue = true;
			}
			size += (int)line.size();
		}
		infileStreamer.close();
	}

	if(abs(size - fileSize) > 5){
		return false;
	}

	return foundTrue;
}
