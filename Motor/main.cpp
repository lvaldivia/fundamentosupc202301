#include <SDL/SDL.h>
#include "MainGame.h"
#include "App.h"

int main(int argc,char** argv) {
	MainGame mainGame;
	mainGame.run();
	system("PAUSE");
	return 0;
}