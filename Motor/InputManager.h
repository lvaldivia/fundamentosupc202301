#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
using namespace std;

class InputManager
{
private:
	unordered_map<unsigned int, bool> keys;
	unordered_map<unsigned int, bool> previuosKey;
	glm::vec2 mouseCoords;
	bool wasKeyDown(unsigned int keyCode);
public:
	InputManager();
	glm::vec2 getMouseCoords() {
		return mouseCoords;
	}
	void update();
	void setMouseCoords(float x, float y);
	void pressKey(unsigned int keyCode);
	void releaseKey(unsigned int keyCode);
	bool isKeyPressed(unsigned int keyCode);
	bool isKeyDown(unsigned int keyCode);
	~InputManager();
};

