#pragma once
#include "GLTexture.h"
#include "TextureCache.h"


class ResourceManager
{
private:
	static TextureCache textureCache;
public:
	static GLTexture getTexture(string texturePath);
};

