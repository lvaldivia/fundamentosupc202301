#pragma once
#include <algorithm>
#include "Game.h"
class App : public Game
{
public:
	App();
	~App();
	virtual void onInit() override;
	virtual void addScreens()override;
	virtual void onExit() override;
private:

};

