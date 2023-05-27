#include "Agent.h"
#include "ResourceManager.h"


void Agent::checkTilePosition(const vector<string>& levelData, vector<glm::vec2>& collideTilePosition, float x, float y)
{
    float tile_with = 64.0f;
    glm::vec2 cornerPos = glm::vec2(floor(x / tile_with));
    //temporalmente es >= 100
    if (cornerPos.x < 0 || cornerPos.x >= 100 || cornerPos.y < 0 || cornerPos.y >= 100) {
        return;
    }
    //temporalmente pos = vacio
    string pos = "";
    if (pos != ".") {
        collideTilePosition.push_back(cornerPos * 
                    tile_with + glm::vec2(tile_with / 2.0f));
    }
}

void Agent::collideWithTile(glm::vec2 tilePos)
{
}

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

bool Agent::collideWithLevel(const vector<string>& levelData)
{
    vector<glm::vec2> collideTilePosition;
    checkTilePosition(levelData, collideTilePosition, 
        position.x, position.y);
    checkTilePosition(levelData, collideTilePosition, 
        position.x + AGENT_WIDTH, position.y);
    checkTilePosition(levelData, collideTilePosition, 
        position.x, position.y + AGENT_WIDTH);
    checkTilePosition(levelData, collideTilePosition, 
        position.x + AGENT_WIDTH, position.y + AGENT_WIDTH);
    if (collideTilePosition.size() == 0) {
        return false;
    }
    for (size_t i = 0; i < collideTilePosition.size(); i++)
    {
        collideWithLevel(collideTilePosition[i]);
    }
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
