#include "Player.h"
#include <SDL/SDL.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(float speed, glm::vec2 position, InputManager* inputManager)
{
	this->path = "Textures/circle.png";
	this->speed = speed;
	this->position = position;
	this->inputManager = inputManager;
	color.set(185, 0, 0, 255);
}

void Player::update(const vector<string>& levelData, vector<Human*>& humans, vector<Zombie*>& zombies)
{
	if (inputManager->isKeyPressed(SDLK_w)) {
		position.y += speed;
	}

	if (inputManager->isKeyPressed(SDLK_s)) {
		position.y -= speed;
	}

	if (inputManager->isKeyPressed(SDLK_a)) {
		position.x -= speed;
	}

	if (inputManager->isKeyPressed(SDLK_d)) {
		position.x += speed;
	}
	collideWithLevel(levelData);
}
