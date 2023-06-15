#include "ScreenList.h"
#include "IGameScreen.h"

ScreenList::ScreenList(Game* game) 
{
    this->game = game;
}


void ScreenList::setScreen(int nextScreen)
{
    currentIndex = nextScreen;
}

void ScreenList::addScreen(IGameScreen* newScreen)
{
    newScreen->screenIndex = screen.size();
    screen.push_back(newScreen);
    newScreen->build();
    newScreen->setParent(game);
}

void ScreenList::destroy()
{
    for (size_t i = 0; i < screen.size(); i++)
    {
        screen[i]->destroy();
    }
    currentIndex = -1;
    screen.resize(0);
}

ScreenList::~ScreenList()
{
    destroy();
}

IGameScreen* ScreenList::getCurrent()
{
    return currentIndex == -1 ? nullptr : screen[currentIndex];
}

IGameScreen* ScreenList::moveNext()
{
    IGameScreen* current = getCurrent();
    if (current->getNextScreen() != -1) {
        currentIndex = current->getNextScreen();
    }
    return getCurrent();
}

IGameScreen* ScreenList::movePrevious()
{
    IGameScreen* current = getCurrent();
    if (current->getPreviousScreen() != -1) {
        currentIndex = current->getPreviousScreen();
    }
    return getCurrent();
}






