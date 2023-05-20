#include "Agent.h"
#include "ResourceManager.h"

Agent::Agent()
{
}

void Agent::draw(SpriteBatch& spriteBatch)
{
    static int textureID = ResourceManager::getTexture(path).id;
    const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    glm::vec4 destRect(position.x, position.y, AGENT_WIDTH, AGENT_WIDTH);
    spriteBatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

bool Agent::collideWithLevel(vector<string>& levelData)
{
    return false;
}

Agent::~Agent()
{
}

bool Agent::collideWithAgent(Agent* agent)
{
    glm::vec2 centerPosA = position + glm::vec2(AGENT_WIDTH / 2);
    glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_WIDTH / 2);
    glm::vec2 dist = centerPosA - centerPosB;
    const float MIN_DISTANCE = AGENT_RADIUS * 2;
    float distance = glm::length(dist);
    float collision = MIN_DISTANCE - distance;
    if (collision > 0) {
        glm::vec2 collisionVec = glm::normalize(dist) * collision;
        position += collisionVec / 2.0f;
        agent->setPosition(agent->getPosition() + (collisionVec / 2.0f));
        return true;
    }
    return false;
}
