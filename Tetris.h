#pragma once
#ifndef TETRIS_H_
#define TETRIS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <bits/stdc++.h>
#include "defs.h"
#include "menu.h"
#include "mixermanager.h"

class Tetris
{
public:
	Tetris()
	{
		// cstr
	}
	~Tetris()
	{
		// dstr
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

	bool init(const char *title);
	bool isGameOver();
	void nextTetrimino();
	void handleEvents();
	void setRectPos(SDL_Rect &rect, int x = 0, int y = 0, int w = BlockW, int h = BlockH);
	void moveRectPos(SDL_Rect &rect, int x, int y);
	void gameplay();
	void instantDrop();
	void updateRender();
	void clean();
	void startGame();
	void renderbutton();


	bool isAlive = true;

    Menu *menu;

    Text* scoreText;

    Text* highscoreText;

    MixerManager* music;
    MixerManager* buttonclick;
    MixerManager* rotateblock;
    MixerManager* harddrop;
    MixerManager* clearrow;

    int isstart = 0;

    int score = 0;

    int highscore = 0;

private:
	SDL_Window *window = NULL;
	SDL_Renderer *render = NULL;
	SDL_Texture *background = NULL, *blocks = NULL;
	SDL_Rect srcR = {0, 0, BlockW, BlockH}, destR = {0, 0, 36, 36};

	SDL_Texture *playingame;
	SDL_Texture *redplayingame;
	SDL_Texture *pauseingame;
	SDL_Texture *redpauseingame;
	SDL_Texture *home;
	SDL_Texture *redhome;


	bool running = false;

	bool isPause = false;

	int field[Lines][Cols] = {0};

	static const int figures[7][4];

	static const int hardfigures[10][4];

	struct Point
	{
		int x, y;
	} items[4], backup[4], next[4];

	//int color = 1;

	int lastcolor = 1;

	int currentcolor = 1;

	int dx = 0;

	bool rotate = false;

	unsigned int delay = 300;

	Uint32 startTime = 0, currentTime = 0;


};

#endif // !TETRIS_H_
