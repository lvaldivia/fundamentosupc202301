#pragma once
#include <glm/glm.hpp>
#include "SpriteBatch.h"
class Bullet
{
private:
	float speed;
	glm::vec2 position;
	glm::vec2 direction;
	int lifetime;
public:
	Bullet(glm::vec2 position, glm::vec2 direction, float speed, int lifetime);
	~Bullet();
	void draw(SpriteBatch& spritebatch);
	bool update();
};

