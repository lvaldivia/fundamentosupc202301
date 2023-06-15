#pragma once
#include <vector>
using namespace std;
class Game;
class IGameScreen;
class ScreenList
{
public:
	ScreenList(Game* game);
	~ScreenList();
	IGameScreen* moveNext();
	IGameScreen* movePrevious();
	void setScreen(int nextScreen);
	void addScreen(IGameScreen* newScreen);
	void destroy();
	IGameScreen* getCurrent();
protected:
	vector<IGameScreen*> screen;
	Game* game;
	int currentIndex = -1;
};

