#include "App.h"
#include "ScreenList.h"

App::App()
{
}

App::~App()
{
}

void App::onInit()
{
}

void App::addScreens()
{
	gamePlayScreen = std::make_unique<GameplayScreen>(&window);
	screenList->addScreen(gamePlayScreen.get());
	screenList->setScreen(gamePlayScreen->getIndex());
}

void App::onExit()
{
}
