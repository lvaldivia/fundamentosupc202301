#include "Agent.h"
#include "ResourceManager.h"


void Agent::checkTilePosition(const vector<string>& levelData, vector<glm::vec2>& collideTilePosition, float x, float y)
{
    glm::vec2 cornesPos = glm::vec2(floor(x / (float)TILE_WIDTH),
        floor(y / (float)TILE_WIDTH));

    if (cornesPos.x < 0 || cornesPos.x >= levelData[0].size() || cornesPos.y < 0 || cornesPos.y >= levelData.size()) {
        return;
    }
    if (levelData[cornesPos.y][cornesPos.x] != '.') {
        collideTilePosition.push_back(cornesPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
    }
}

void Agent::collideWithTile(glm::vec2 tilePos)
{
    const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
    const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

    glm::vec2 centerPosition = position + glm::vec2(AGENT_RADIUS);
    glm::vec2 distVec = centerPosition - tilePos;
    float xdepth = MIN_DISTANCE - abs(distVec.x);
    float ydepth = MIN_DISTANCE - abs(distVec.y);

    if (xdepth > 0 || ydepth > 0) {
        if (std::max(xdepth, 0.0f) < std::max(ydepth, 0.0f)) {
            if (distVec.x < 0) {
                position.x -= xdepth;
            }
            else {
                position.x += xdepth;
            }
        }
        else {
            if (distVec.y < 0) {
                position.y -= ydepth;
            }
            else {
                position.y += ydepth;
            }
        }
    }
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
    std::vector<glm::vec2> collideTilePosition;


    checkTilePosition(levelData, collideTilePosition, position.x, position.y);

    checkTilePosition(levelData, collideTilePosition, position.x + AGENT_WIDTH, position.y);
    checkTilePosition(levelData, collideTilePosition, position.x, position.y + AGENT_WIDTH);
    checkTilePosition(levelData, collideTilePosition, position.x + AGENT_WIDTH, position.y + AGENT_WIDTH);

    if (collideTilePosition.size() == 0) return false;

    for (size_t i = 0; i < collideTilePosition.size(); i++)
    {
        collideWithTile(collideTilePosition[i]);
    }

    return true;
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
