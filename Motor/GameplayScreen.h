#pragma once
#include <SDL/SDL.h>
#include "IGameScreen.h"
#include "Camera2D.h"
#include "Window.h"
#include "GLTexture.h"
#include "SpriteBatch.h"
#include "HLSLProgram.h"

class GameplayScreen : public IGameScreen
{
private:
	HLSLProgram program;
	Camera2D camera2d;
	Window* window = nullptr;
	SpriteBatch spriteBatch;
public:
	GameplayScreen(Window* window);
	~GameplayScreen();
	virtual void checkInput()override;
	virtual void initSystem()override;
	virtual void build()override;
	virtual void destroy()override;
	virtual void onExit()override;
	virtual void onEntry()override;
	virtual void draw()override;
	virtual void update()override;
	virtual void initGUI()override;
	virtual int getNextScreen() const override;
	virtual int getPreviousScreen() const override;
};

