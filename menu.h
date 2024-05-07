// Menu.h
#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include "text.h"

class Menu
{
public:
    Menu(SDL_Renderer *renderer);
    ~Menu();

    void show();
    void showins();
    void handleEvents();
    int getState() {return state;}

private:
    int state;
    bool ismusic = true;
    bool issound = true;

    SDL_Color textcolor = {255, 255, 255, 255};

    SDL_Renderer *renderer;

    SDL_Texture *logo;

    SDL_Texture *playButton;
    SDL_Texture *redplayButton;

    SDL_Texture *instructionsButton;
    SDL_Texture *redinstructionsButton;

    SDL_Texture *backbutton;
    SDL_Texture *redbackbutton;

    SDL_Texture *quitButton;
    SDL_Texture *redquitButton;

    SDL_Texture *musicButton;
    SDL_Texture *redmusicButton;

    SDL_Texture *muteMusicButton;
    SDL_Texture *redmuteMusicButton;

    SDL_Texture *soundButton;
    SDL_Texture *redsoundButton;

    SDL_Texture *muteSoundButton;
    SDL_Texture *redmuteSoundButton;


    SDL_Texture *menuBack;

    void loadTextures();
    void freeTextures();

    Text* instructions;
    Text* moveRL;
    Text* rotateblock;
    Text* softdrop;
    Text* harddrop;
    Text* pause_play;
    Text* instant_quit;
};

#endif // MENU_H
