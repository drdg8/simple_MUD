#ifndef _GAME_HEAD_
#define _GAME_HEAD_

#include "Scene.h"
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;


class Game
{
public:
	Game();
	virtual ~Game();

	void mainMenu();

	void startMenu();

	void initGame();

	void endGame();

	void createCharacter();

	void storeCharacter();

	void loadCharacter();

	void play();

	std::vector<std::string> split(std::string &str, char c);
	// Accessors
	inline int getPlayingState() const {
		return this->isPlaying;
	}

	//Modifiers
private:
	int choice;

	// 0 to exit, 1 to mainMenu, 2 to travel
	int isPlaying;

	//Character related
	Character activeCharacter;

	std::vector<Character> characters;

	Inventory activeInventory;

	std::string fileName;
};

#endif