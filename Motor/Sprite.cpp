#include "Sprite.h"
#include <cstddef>
#include "Vertex.h"
#include "ResourceManager.h"


Sprite::Sprite() {
	vboID = 0;
}

void Sprite::init(float x, float y, int width, int height,string texturePath) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	if (vboID == 0) {
		glGenBuffers(1, &vboID);
	}

	texture = ResourceManager::getTexture(texturePath);

	Vertex vertexData[6];
	vertexData[0].setUV(1.0f,1.0f);
	vertexData[1].setUV(0.0f,1.0f);
	vertexData[2].setUV(0.0f,0.0f);
	vertexData[3].setUV(0.0f, 0.0f);
	vertexData[4].setUV(1.0f, 0.0f);
	vertexData[5].setUV(1.0f, 1.0f);

	vertexData[0].setPosition(x + width, y + height);
	vertexData[1].setPosition(x, y + height);
	vertexData[2].setPosition(x, y );
	vertexData[3].setPosition(x , y);
	vertexData[4].setPosition(x + width, y);
	vertexData[5].setPosition(x + width, y + height);

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].setColor(255, 255, 0, 255);
	}
	vertexData[2].setColor(255, 0, 255, 255);
	vertexData[3].setColor(0, 255, 255, 255);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
}
void Sprite::draw() {
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,position));

	//glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
			(void*)offsetof(Vertex, uv));


	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


Sprite::~Sprite() {
	if (vboID != 0) {
		glDeleteBuffers(1, &vboID);
	}
}