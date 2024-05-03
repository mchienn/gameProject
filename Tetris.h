#pragma once
#ifndef TETRIS_H_
#define TETRIS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#define ScreenW 600
#define ScreenH 960
#define BlockW 36
#define BlockH 36
#define Lines 20
#define Cols 10

class Tetris
{
public:
	Tetris()
	{
	    //cstr
	}
	~Tetris()
	{
	    //dstr
	}

	void setCurrentTime(Uint32 t)
	{
		currentTime = t;
	}

	bool isrunning()
	{
		return running;
	}

	bool isvalid();

	bool init(const char* title);
	void nextTetrimino();
	void handleEvents();
	void setRectPos(SDL_Rect& rect, int x = 0, int y = 0, int w = BlockW, int h = BlockH);
	void moveRectPos(SDL_Rect& rect, int x, int y);
	void gameplay();
	void updateRender();
	void clean();

private:

	SDL_Window* window = NULL;
	SDL_Renderer* render = NULL;
	SDL_Texture* background = NULL, * blocks = NULL;
	SDL_Rect srcR = { 0, 0, BlockW, BlockH }, destR = { 0, 0, 32, 32 };

	bool running = false;

	bool isAlive = true;

	bool isPause = false;

	int field[Lines][Cols] = { 0 };

	static const int figures[7][4];

	struct Point{int x, y;} items[4], backup[4], next[4];

	int color = 1;

	int dx = 0;

	bool rotate = false;

	unsigned int delay = 300;

	Uint32 startTime = 0, currentTime = 0;
};


#endif // !TETRIS_H_