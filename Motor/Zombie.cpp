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

Human* Zombie::getNearestHuman(vector<Human*>& humans)
{
	Human* closeHuman = nullptr;
	float smallestDistance = 888888888.0f;
	for (size_t i = 0; i < humans.size(); i++)
	{
		glm::vec2 dist = humans[i]->getPosition() - position;
		float distance = glm::length(dist);
		if (distance < smallestDistance) {
			smallestDistance = distance;
			closeHuman = humans[i];
		}
	}
	return closeHuman;
}

void Zombie::update(const std::vector<std::string>& levelData,std::vector<Human*>& humans,std::vector<Zombie*>& zombies) {
	collideWithLevel(levelData);
	Human* closestHuman = getNearestHuman(humans);
	if (closestHuman != nullptr) {
		glm::vec2 direction =
			glm::normalize(closestHuman->getPosition() - position);
		position += direction * speed;
	}

}




Zombie::~Zombie()
{
}
