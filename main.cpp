#include "Tetris.h"
#include <bits/stdc++.h>
int main(int argc, char *argv[])
{
	using namespace std;
	srand(time(0));
	Tetris *tetris = new Tetris();
	const char *title = "Tetris";
	if (tetris->init(title))
	{
		while (tetris->isrunning())
		{

			if (!tetris->isAlive)
			{
				//switch to the gameover screen
				break;
			}
			tetris->setCurrentTime(SDL_GetTicks());
			tetris->handleEvents();
			tetris->gameplay();
			tetris->updateRender();
		}
	}
	else
	{
		cout << "Failed to initialize";
	}
	tetris->clean();
	return 0;
}
