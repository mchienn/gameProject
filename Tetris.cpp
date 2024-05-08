#include <iostream>
#include <fstream>
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
				menu = new Menu(render);
				scoreText = new Text(render, "font/gomarice_mix_bit_font.ttf", SmallText, "Score         : 0", {255, 255, 255, 255});
				highscoreText = new Text (render, "font/gomarice_mix_bit_font.ttf", SmallText, "High Score: ", {255, 255, 255, 255});
				std::ifstream file("highscore.txt");
				file >> highscore;
                file.close();
                std::string newMessage = "High Score : " + std::to_string(highscore);
                highscoreText->update(render, newMessage, "font/gomarice_mix_bit_font.ttf", SmallText, {255, 255, 255, 255});
                highscoreText->display(200, 75, render);

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

void Tetris::renderbutton()
{
	SDL_Rect pauseplay = {50, 75, SquareButtonW, SquareButtonH};
	SDL_Rect homebut = {125, 75, SquareButtonW, SquareButtonH};

	if (pauseingame == NULL)
	{
		SDL_Log("Error \%s", SDL_GetError());
	}

	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if (isPause == false)
	{
		if (mouseX >= 50 && mouseX <= 50 + SquareButtonW &&
			mouseY >= 75 && mouseY <= 75 + SquareButtonH)
		{
			SDL_RenderCopy(render, redpauseingame, NULL, &pauseplay);
		}
		else
		{
			SDL_RenderCopy(render, pauseingame, NULL, &pauseplay);
		}
	}
	else
	{
		if (mouseX >= 50 && mouseX <= 50 + SquareButtonW &&
			mouseY >= 75 && mouseY <= 75 + SquareButtonH)
		{
			SDL_RenderCopy(render, redplayingame, NULL, &pauseplay);
		}
		else
		{
			SDL_RenderCopy(render, playingame, NULL, &pauseplay);
		}
	}

	if (mouseX >= 125 && mouseX <= 125 + SquareButtonW &&
		mouseY >= 75 && mouseY <= 75 + SquareButtonH)
	{
		SDL_RenderCopy(render, redhome, NULL, &homebut);
	}
	else
	{
		SDL_RenderCopy(render, home, NULL, &homebut);
	}

	SDL_RenderPresent(render);
}

void Tetris::nextTetrimino()
{
    score += 10;

	int n = rand() % 7;

	for (int i = 0; i < 4; i++)
	{
		items[i] = next[i];
	}
	currentcolor = lastcolor;
	lastcolor = 1 + n;

	for (int i = 0; i < 4; i++)
	{
		next[i].x = figures[n][i] % 4;
		next[i].y = (int)(figures[n][i] / 4);
	}

	for (int i = 0; i < 4; i++)
	{
		items[i].x += Cols / 2 - 2;
		items[i].y = items[i].y;
	}

	if (isGameOver())
	{
		menu->state = GAMEOVER;
		isstart = 0;
		for (int i = 0; i < Lines; i ++)
        {
            for (int j = 0; j < Cols; j ++)
            {
                field[i][j] = 0;
            }
        }
		return;
	}
}

void Tetris::handleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		int x = e.button.x;
		int y = e.button.y;

		switch (e.type)
		{
		case SDL_MOUSEBUTTONDOWN:
		{
			if (x >= 50 && x <= 50 + SquareButtonW &&
				y >= 75 && y <= 75 + SquareButtonH)
			{
				isPause = !isPause;
				while (isPause && SDL_WaitEvent(&e))
				{
					renderbutton();

					if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p)
					{
						isPause = false;
						break;
					}
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						x = e.button.x;
						y = e.button.y;
						if (x >= 50 && x <= 50 + SquareButtonW &&
							y >= 75 && y <= 75 + SquareButtonH)
						{
							isPause = false;
							break;
						}
						if (x >= 125 && x <= 125 + SquareButtonW &&
							y >= 75 && y <= 75 + SquareButtonH)
						{
							menu->state = MENU;
							break;
						}
					}
				}
			}
			if (x >= 125 && x <= 125 + SquareButtonW &&
				y >= 75 && y <= 75 + SquareButtonH)
			{
				menu->state = MENU;
				isPause = false;
			}
			break;
		}
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
				isPause = !isPause;
				while (isPause && SDL_WaitEvent(&e))
				{
					renderbutton();

					if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p)
					{
						isPause = false;
						break;
					}
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						x = e.button.x;
						y = e.button.y;
						if (x >= 50 && x <= 50 + SquareButtonW &&
							y >= 75 && y <= 75 + SquareButtonH)
						{
							isPause = false;
							break;
						}
						if (x >= 125 && x <= 125 + SquareButtonW &&
							y >= 75 && y <= 75 + SquareButtonH)
						{
							menu->state = MENU;
							isPause = false;
							break;
						}
					}
				}
				break;
			case SDLK_ESCAPE:
				running = false;
				break;
			case SDLK_SPACE:
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
		if (items[3].x - items[0].x == 1 && items[1].x - items[2].x == 1)
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
				field[backup[i].y][backup[i].x] = currentcolor;
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

        if (count == Cols)
        {
            score += 100;
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


    std::string newMessage = "Score            : " + std::to_string(score);
    scoreText->update(render, newMessage, "font/gomarice_mix_bit_font.ttf", SmallText, {255, 255, 255, 255});
    scoreText->display(200, 105, render);

    if (score > highscore)
    {
        highscore = score;
        std::ofstream file ("highscore.txt");
        file << highscore;
        file.close();
    }

    std::string newHighscore = "High Score : " + std::to_string(highscore);
    highscoreText->update(render, newHighscore, "font/gomarice_mix_bit_font.ttf", SmallText, {255, 255, 255, 255});
    highscoreText->display(200, 75, render);


	for (int i = 0; i < 4; i++)
	{
		setRectPos(srcR, lastcolor * BlockW, 0);
		setRectPos(destR, 410 + next[i].x * BlockW, 300 + next[i].y * BlockH);
		SDL_RenderCopy(render, blocks, &srcR, &destR);
	}

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
		setRectPos(srcR, currentcolor * BlockW, 0);
		setRectPos(destR, items[i].x * BlockW, items[i].y * BlockH);
		moveRectPos(destR, BlockW, ScreenH - (Lines + 1) * BlockH);
		SDL_RenderCopy(render, blocks, &srcR, &destR);
	}

	renderbutton();
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
				field[backup[i].y][backup[i].x] = currentcolor;
			nextTetrimino();
			score += 50;
			break;
		}
	}
}

bool Tetris::isGameOver()
{
	for (int x = 0; x < Cols; x++)
		if (field[1][x] != 0)
		{
			return true;
		}
	return false;
}

void Tetris::startGame()
{
    isstart++;
    score = 0;
	srand(time(0));

	// load the images (background and blocks
	SDL_Surface *loadSurf = IMG_Load("img/background2.png");
	background = SDL_CreateTextureFromSurface(render, loadSurf);
	SDL_FreeSurface(loadSurf);
	loadSurf = IMG_Load("img/blocks.png");
	blocks = SDL_CreateTextureFromSurface(render, loadSurf);
	SDL_FreeSurface(loadSurf);

	playingame = IMG_LoadTexture(render, "img/playingame.png");
	redplayingame = IMG_LoadTexture(render, "img/redplayingame.png");
	pauseingame = IMG_LoadTexture(render, "img/pauseingame.png");
	redpauseingame = IMG_LoadTexture(render, "img/redpauseingame.png");
	home = IMG_LoadTexture(render, "img/home.png");
	redhome = IMG_LoadTexture(render, "img/redhome.png");

	int n = rand() % 7;

	for (int i = 0; i < 4; i++)
	{
		next[i].x = figures[n][i] % 4;
		next[i].y = (int)(figures[n][i] / 4);
	}

	for (int i = 0; i < 4; i++)
	{
		items[i].x = Cols / 2 - 2 + figures[(n + 1) % 7][i] % 4;
		items[i].y = (int)(figures[(n + 1) % 7][i] / 4);
	}
}
