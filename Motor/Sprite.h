#pragma once
#include <GL/glew.h>
using namespace std;
class Sprite
{
private:
	float x;
	float y;
	int width;
	int height;
	GLuint vboID;
public:
	Sprite();
	~Sprite();
	void init(float x, float y, int width, int height);
	void draw();
};

