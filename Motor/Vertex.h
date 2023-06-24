#pragma once
#include <GL/glew.h>

struct Position {
	float x;
	float y;
	void set(float _x, float _y) {
		x = _x;
		y = _y;
	}
};

struct Color {
	Color(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a) {
		set(_r, _g, _b, _a);
	}
	Color() : r(0), g(0), b(0), a(0) {}
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
	void set(GLubyte _r,GLubyte _g,GLubyte _b,GLubyte _a) {
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
};

struct UV {
	float u;
	float v;
	void set(float _u, float _v) {
		u = _u;
		v = _v;
	}
};

struct Vertex {
	Position position;
	Color color;
	UV uv;
	void setPosition(float x,float y) {
		position.set(x, y);
	}
	void setColor(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a) {
		color.set(_r, _g, _b, _a);
	}
	void setUV(float u, float v) {
		uv.set(u, v);
	}
};
