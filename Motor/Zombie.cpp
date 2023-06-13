#include "Zombie.h"
#include "Human.h"


Zombie::Zombie()
{
}

void Zombie::init(float speed, glm::vec2 position) {
	this->path = "Textures/circle.png";
	this->speed = speed;
	this->position = position;
	color.set(0, 255, 0, 255);
}

void Zombie::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies) {
	collideWithLevel(levelData);

}




Zombie::~Zombie()
{
}
