#pragma once
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "GLTexture.h"
#include <string>

const float AGENT_WIDTH = 60.f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class Agent
{
protected:
	string path;
	glm::vec2 position;
	float speed;
	Color color;
public:
	Agent();
	glm::vec2 getPosition() {
		return position;
	}
	void setPosition(glm::vec2 position) {
		this->position = position;
	}
	void draw(SpriteBatch& spriteBatch);
	bool collideWithLevel(vector<string>& levelData);
	virtual ~Agent();
	bool collideWithAgent(Agent* agent);
};

