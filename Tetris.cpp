#include <iostream>
#include "Tetris.h"
/*
	0	1	2	3
	4	5	6	7
*/
const int Tetris::figures[7][4] =
	{
		0, 1, 2, 3, // I
		0, 4, 5, 6, // J
		2, 6, 5, 4, // L
		1, 2, 5, 6, // O
		2, 1, 5, 4, // S
		1, 4, 5, 6, // T
		0, 1, 5, 6, // Z
};
bool Tetris::init(const char *title)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenW, ScreenH, SDL_WINDOW_RESIZABLE);
		if (window != NULL)
		{
			render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (render != NULL)
			{
				SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
				int imgFlags = IMG_INIT_PNG;
				int initted = IMG_Init(imgFlags);
				if ((initted & imgFlags) != imgFlags)
					std::cout << "Failed to init required png support\n"
							  << "IMG_Init() Error : " << IMG_GetError() << std::endl;
				SDL_Surface *loadSurf = IMG_Load("img/background.png");
				background = SDL_CreateTextureFromSurface(render, loadSurf);
				SDL_FreeSurface(loadSurf);
				loadSurf = IMG_Load("img/blocks.png");
				blocks = SDL_CreateTextureFromSurface(render, loadSurf);
				SDL_FreeSurface(loadSurf);
				nextTetrimino();
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;

	running = true;
	return true;
}

void Tetris::nextTetrimino()
{
	int n = rand() % 7;
	color = 1 + n;
	for (int i = 0; i < 4; i++)
	{
		items[i].x = Cols / 2 - 2 + figures[n][i] % 4;
		items[i].y = int(figures[n][i] / 4);
	}
}

void Tetris::handleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_z:
				rotate = true;
				break;
			case SDLK_LEFT:
				dx = -1;
				break;
			case SDLK_RIGHT:
				dx = 1;
				break;
			case SDLK_p:
				isPause = (isPause == true ? false : true);
				if (isPause == true)
				{
					while (SDL_WaitEvent(&e))
					{
						if (e.type == SDL_KEYDOWN)
						{
							if (e.key.keysym.sym == SDLK_p)
							{
								break;
							}
						}
					}
					isPause = false;
				}
				break;
			case SDLK_ESCAPE:
				// instantly quit the game
				running = false;
				break;

			case SDLK_SPACE:
				// instantly drop
				instantDrop();
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_DOWN])
		delay = 60;
}

void Tetris::setRectPos(SDL_Rect &rect, int x, int y, int w, int h)
{
	rect = {x, y, w, h};
}

void Tetris::moveRectPos(SDL_Rect &rect, int x, int y)
{
	rect.x += x;
	rect.y += y;
}

bool Tetris::isvalid()
{
	for (int i = 0; i < 4; i++)
		if (items[i].x < 0 || items[i].x >= Cols || items[i].y >= Lines)
			return false;
		else if (field[items[i].y][items[i].x])
			return false;
	return true;
}

void Tetris::gameplay()
{

	// save the blocks
	for (int i = 0; i < 4; i++)
		backup[i] = items[i];
	// move
	if (dx)
	{
		for (int i = 0; i < 4; i++)
		{
			items[i].x += dx;
		}
		if (!isvalid())
			for (int i = 0; i < 4; i++)
				items[i] = backup[i];
	}

	// rotate
	if (rotate)
	{
		// the square cannot rotate
		if (items[0].x == 1 && items[1].x == 2 && items[2].x == 1 && items[3].x == 2)
		{
		}
		else
		{
			Point p = items[2]; // center of rotation
			for (int i = 0; i < 4; i++)
			{
				int x = items[i].y - p.y;
				int y = items[i].x - p.x;
				items[i].x = p.x - x;
				items[i].y = p.y + y;
			}
			// check the rotate valid
			if (!isvalid())
				for (int i = 0; i < 4; i++)
					items[i] = backup[i];
		}
	}

	// tick
	if (currentTime - startTime > delay)
	{
		for (int i = 0; i < 4; i++)
			backup[i] = items[i];
		for (int i = 0; i < 4; i++)
		{
			items[i].y++;
		}
		SDL_Delay(60);
		if (!isvalid())
		{
			for (int i = 0; i < 4; i++)
				field[backup[i].y][backup[i].x] = color;
			nextTetrimino();
		}
		startTime = SDL_GetTicks();
	}

	// check lines

	int k = Lines - 1;
	for (int i = k; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < Cols; j++)
		{
			if (field[i][j] != 0)
				count++;
			field[k][j] = field[i][j];
		}
		if (count < Cols)
			k--;
	}
	dx = 0;
	rotate = false;
	delay = 300;
}

void Tetris::updateRender()
{
	SDL_RenderCopy(render, background, NULL, NULL);
	for (int i = 0; i < Lines; i++)
		for (int j = 0; j < Cols; j++)
			if (field[i][j])
			{
				setRectPos(srcR, field[i][j] * BlockW);
				setRectPos(destR, j * BlockW, i * BlockH);
				moveRectPos(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
				SDL_RenderCopy(render, blocks, &srcR, &destR);
			}
	for (int i = 0; i < 4; i++)
	{
		setRectPos(srcR, color * BlockW);
		setRectPos(destR, items[i].x * BlockW, items[i].y * BlockH);
		moveRectPos(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
		SDL_RenderCopy(render, blocks, &srcR, &destR);
	}

	SDL_RenderPresent(render);
}

void Tetris::clean()
{
	SDL_DestroyTexture(blocks);
	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(render);
	IMG_Quit();
	SDL_Quit();
}

void Tetris::instantDrop()
{
	while (true)
	{
		for (int i = 0; i < 4; i++)
			backup[i] = items[i];
		for (int i = 0; i < 4; i++)
			items[i].y++;
		if (!isvalid())
		{
			for (int i = 0; i < 4; i++)
				field[backup[i].y][backup[i].x] = color;
			nextTetrimino();
			break;
		}
	}
}
