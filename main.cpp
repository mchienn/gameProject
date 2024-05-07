#include "Tetris.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[])
{

	srand(time(0));
	Tetris *tetris = new Tetris();
	const char *title = "Tetris";
	int counT = 0;
	if (tetris->init(title))
	{
		while (tetris->isrunning())
		{

			if (tetris->menu->getState() == MENU)
			{
				tetris->menu->show();
				tetris->menu->handleEvents();
			}
			else if (tetris->menu->getState() == INSTRUCTIONS)
			{
			    tetris->menu->showins();
			    tetris->menu->handleEvents();
			}
			else if (tetris->menu->getState() == PLAY)
			{
				if (counT == 0)
                {
                    tetris->nextTetrimino();
                    tetris->startGame();
                    counT++;
                }
				tetris->handleEvents();
				tetris->gameplay();
				tetris->updateRender();
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
