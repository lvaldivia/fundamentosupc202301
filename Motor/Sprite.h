#pragma once
#include <GL/glew.h>
#include "GLTexture.h"
#include <string>
using namespace std;

class Sprite
{
private:
	float x;
	float y;
	int width;
	int height;
	GLuint vboID;
	GLTexture texture;
public:
	Sprite();
	~Sprite();
	void init(float x, float y, int width, int height,string texturePath);
	void draw();
};

