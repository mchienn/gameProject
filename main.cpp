#include "Tetris.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[])
{

	srand(time(0));
	Tetris *tetris = new Tetris();
	const char *title = "Tetris";
	if (tetris->init(title))
	{
		while (tetris->isrunning())
		{
			switch (tetris->menu->ismusic)
			{
			case true:
				tetris->music->continueMusic();
				break;
			case false:
				tetris->music->stopMusic();
				break;
			}

			switch (tetris->menu->getState())
			{
			case MENU:
				tetris->menu->show();
				tetris->menu->handleEvents();
				break;
			case INSTRUCTIONS:
				tetris->menu->showins();
				tetris->menu->handleEvents();
				break;
			case GAMEOVER:
				tetris->menu->showover();
				tetris->menu->handleEvents();
				break;
			case PLAY:
				if (tetris->isstart == 0)
				{
					tetris->nextTetrimino();
					tetris->startGame();
				}
				tetris->handleEvents();
				tetris->gameplay();
				tetris->updateRender();
				break;
			default:
				break;
			}
			tetris->setCurrentTime(SDL_GetTicks());
		}
	}
	else
	{
		cout << "Failed to initialize";
	}
	tetris->clean();
	return 0;
}
