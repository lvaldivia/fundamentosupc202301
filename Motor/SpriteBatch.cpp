#include "SpriteBatch.h"
#include <algorithm>

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::createVertexArray()
{
	if (vbo == 0) {
		glGenBuffers(1, &vbo);
	}
	if (vba == 0) {
		glGenVertexArrays(1, &vba);
	}
	glBindVertexArray(vba);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, uv));
	glBindVertexArray(0);
}

void SpriteBatch::begin(GlyphSortType type)
{
	sortType = type;
	renderBatches.clear();
	glyphs.clear();
}

void SpriteBatch::end()
{
	glyphPointers.resize(glyphs.size());
	for (size_t i = 0; i < glyphs.size(); i++)
	{
		glyphPointers[i] = &glyphs[i];
	}
	sortGlyph();
	createRenderBatches();
}

void SpriteBatch::createRenderBatches()
{
	vector<Vertex>vertices;
	vertices.resize(glyphs.size() * 6);
	if (glyphs.size() == 0) {
		return;
	}
	int cv = 0;
	int offset = 0;
	renderBatches.emplace_back(offset, 6, glyphPointers[0]->texture);
	vertices[cv++] = glyphPointers[0]->topLeft;
	vertices[cv++] = glyphPointers[0]->bottomLeft;
	vertices[cv++] = glyphPointers[0]->bottomRight;
	vertices[cv++] = glyphPointers[0]->bottomRight;
	vertices[cv++] = glyphPointers[0]->topRight;
	vertices[cv++] = glyphPointers[0]->topLeft;
	offset += 6;
	for (int i = 1; i < glyphPointers.size(); i++)
	{
		if (glyphPointers[i]->texture != glyphPointers[i-1]->texture) {
			renderBatches.emplace_back(offset, 6, glyphPointers[1]->texture);
		}
		else {
			renderBatches.back().numVertices += 6;
		}
		vertices[cv++] = glyphPointers[i]->topLeft;
		vertices[cv++] = glyphPointers[i]->bottomLeft;
		vertices[cv++] = glyphPointers[i]->bottomRight;
		vertices[cv++] = glyphPointers[i]->bottomRight;
		vertices[cv++] = glyphPointers[i]->topRight;
		vertices[cv++] = glyphPointers[i]->topLeft;
		offset += 6;
	}
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr,
		GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex),
		vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(vba);
	for (size_t i = 0; i < renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, renderBatches[i].offset,
			renderBatches[i].numVertices);
}
	glBindVertexArray(0);
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color)
{
	glyphs.emplace_back(destRect, uvRect, texture, depth, color);
}

void SpriteBatch::sortGlyph()
{
	switch (sortType)
	{
	case GlyphSortType::FRONT_TO_BACK:
		stable_sort(glyphPointers.begin(), glyphPointers.end(), compareFrontToBack);
		break;

	case GlyphSortType::BACK_TO_FRONT:
		stable_sort(glyphPointers.begin(), glyphPointers.end(), compareBackToFront);
		break;

	case GlyphSortType::TEXTURE:
		stable_sort(glyphPointers.begin(), glyphPointers.end(), compareTexture);
		break;
	}
}

SpriteBatch::SpriteBatch()
{
}

SpriteBatch::~SpriteBatch()
{
}


bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
{
	return (a->depth < b->depth);
}

bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
{
	return (a->depth > b->depth);
}

bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
{
	return (a->texture > b->texture);
}
