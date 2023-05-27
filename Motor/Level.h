#pragma once
#include <string>
#include <vector>
#include "SpriteBatch.h"

using namespace std;
const int TILE_WIDTH = 64;
class Level
{
private:
	vector<string> levelData;
	int numHumans;
	void parseLevel();
	glm::vec2 playerPosition;
	vector<glm::vec2> zombiesPosition;
public:
	int getNumHumans()const {
		return numHumans;
	}
	glm::vec2 getPlayerPosition()const {
		return playerPosition;
	}
	vector<glm::vec2> getZombiesPosition() {
		return zombiesPosition;
	}
	vector<string> getLevelData() {
		return levelData;
	}
	Level(const string& fileName);
	void draw();
	SpriteBatch spriteBatch;
};

