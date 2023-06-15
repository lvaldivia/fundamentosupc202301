#include "Bullet.h"
#include "ResourceManager.h"
#include "GLTexture.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float speed, int lifetime)
{
    this->lifetime = lifetime;
    this->direction = direction;
    this->speed = speed;
    this->position = position;
}

Bullet::~Bullet()
{
}

void Bullet::draw(SpriteBatch& spritebatch)
{
    Color color;
    color.set(255, 255, 255, 255);
    glm::vec4 uv(0.0f,0.0f, 1.0f, 1.0f);
    static GLTexture texture = ResourceManager::getTexture("Textures/Circle.png");
    glm::vec4 posAndSize = glm::vec4(position.x, position.y, 15, 15);
    spritebatch.draw(posAndSize, uv, texture.id, 0.0f, color);
}

bool Bullet::update()
{
    position += direction * speed;
    lifetime--;
    if (lifetime == 0) {
        return true;
    }
    return false;
}
