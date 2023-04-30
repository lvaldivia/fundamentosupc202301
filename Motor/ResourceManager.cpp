#include "ResourceManager.h"


TextureCache ResourceManager::textureCache;

GLTexture ResourceManager::getTexture(string texturePath) {
	return textureCache.getTexture(texturePath);
}