#pragma once
#include <GL/glew.h>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <vector>
using namespace std;

enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

class RenderBatch {
public:
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
	RenderBatch(GLuint offset,GLuint numVertices, GLuint texture){
		this->numVertices = numVertices;
		this->offset = offset;
		this->texture = texture;
	}
};

class Glyph {
public:
	Glyph() {}
	Glyph(const glm::vec4& desRect,const glm::vec4& uvRect, 
		GLuint texture, float depth, const Color& color ) {
		this->texture = texture;
		this->depth = depth;
		topLeft.color = color;
		topLeft.setPosition(desRect.x, desRect.y + desRect.w);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
		bottomLeft.color = color;
		bottomLeft.setPosition(desRect.x, desRect.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);
		bottomRight.color = color;
		bottomRight.setPosition(desRect.x + desRect.z, desRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
		topRight.color = color;
		topRight.setPosition(desRect.x + desRect.z, desRect.y + desRect.w);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	}
	GLuint texture;
	float depth;
	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};
class SpriteBatch
{
private:
	GLuint vbo;
	GLuint vba;
	vector<Glyph> glyphs;
	vector<Glyph*> glyphPointers;
	vector<RenderBatch> renderBatches;
	GlyphSortType sortType;
	void createVertexArray();
	void sortGlyph();
	void createRenderBatches();
public:
	SpriteBatch();
	~SpriteBatch();
	void init();
	void begin(GlyphSortType type = GlyphSortType::TEXTURE);
	void end();
	void draw(const glm::vec4& destRect, const glm::vec4& uvRect,
		GLuint texture, float depth, const Color& color);
	void renderBatch();
	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);
};

