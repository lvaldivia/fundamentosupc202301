#pragma once
#include <SDL/SDL.h>
#include <GL/eglew.h>
#include "Sprite.h"
#include "HLSLProgram.h"
#include "Window.h"
#include "Camera2D.h"
#include "InputManager.h"

enum class GameState {
	PLAY,EXIT
};

class MainGame
{
private:
	int width;
	int height;
	float time;
	Window window;
	HLSLProgram program;
	Sprite sprite;
	Camera2D camera2D;
	InputManager inputManager;
	void init();
	void processInput();
	void initShaders();
	void handleInput();
public:
	MainGame();
	~MainGame();
	GameState gameState;
	
	void run();
	void draw();
	void update();
};

