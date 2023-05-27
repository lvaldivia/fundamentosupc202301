#pragma once
#include "Human.h"
#include "InputManager.h"

class Player : public Human
{
protected:
	InputManager* inputManager;
public:
	Player();
	~Player();
	void init(float speed, glm::vec2 position,InputManager* inputManager);
	void update(const vector<string>& levelData, vector<Human*>& humans,
		vector<Zombie*>& zombies);
};

