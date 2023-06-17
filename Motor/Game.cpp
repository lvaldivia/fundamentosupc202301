#include "Game.h"
#include "ScreenList.h"
#include "IGameScreen.h"

Game::Game()
{
    screenList = std::make_unique<ScreenList>(this);
}

bool Game::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    initSystems();
    onInit();
    addScreens();
    currentScreen = screenList->getCurrent();
    currentScreen->onEntry();
    currentScreen->setRunning();
    return true;
}

void Game::draw()
{
    if (currentScreen && currentScreen->getState() == ScreenState::RUNNING) {
        currentScreen->draw();
    }
}

bool Game::initSystems()
{
    window.create("Juego", 760, 500, 0);
    return true;
}



void Game::run()
{
    if (!init())return;
    isRunning = true;
    while (isRunning) {
        inputManager.update();
        update();
        draw();
        window.swapWindow();
    }
}

void Game::exit()
{
    currentScreen->onExit();
    if (screenList) {
        screenList->destroy();
        screenList.reset();
    }
    isRunning = false;
}

void Game::update()
{
    if (currentScreen) {
        switch (currentScreen->getState())
        {
        case ScreenState::RUNNING:
            currentScreen->update();
            break;
        case ScreenState::CHANGE_NEXT:
            currentScreen->onExit();
            currentScreen = screenList->moveNext();
            if (currentScreen) {
                currentScreen->setRunning();
                currentScreen->onEntry();
            }
            break;
        case ScreenState::CHANGE_PREVIOUS:
            currentScreen->onExit();
            currentScreen = screenList->movePrevious();
            if (currentScreen) {
                currentScreen->setRunning();
                currentScreen->onEntry();
            }
            break;
        case ScreenState::EXIT_APPLICATION:
            exit();
            break;
        }
    }
}

void Game::onSDLEvent(SDL_Event& event)
{
}

Game::~Game()
{
}








