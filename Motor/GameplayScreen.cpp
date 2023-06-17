#include "GameplayScreen.h"
#include "Game.h"

GameplayScreen::GameplayScreen(Window* window)
{
	this->window = window;
}

GameplayScreen::~GameplayScreen()
{
}

void GameplayScreen::checkInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		game->onSDLEvent(event);
	}
}


void GameplayScreen::onEntry()
{
	initSystem();
	initGUI();
	spriteBatch.init();
	camera2d.init(window->getScreenWidth(), window->getScreenHeight());
}

void GameplayScreen::initSystem()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPosition");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();
}

void GameplayScreen::build()
{
}

void GameplayScreen::destroy()
{
}

void GameplayScreen::onExit()
{
}



void GameplayScreen::draw()
{
}

void GameplayScreen::update()
{
}

void GameplayScreen::initGUI()
{
}

int GameplayScreen::getNextScreen() const
{
	return 0;
}

int GameplayScreen::getPreviousScreen() const
{
	return 0;
}
