// Menu.h
#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "text.h"
#include "mixermanager.h"

class Menu
{
public:
    Menu(SDL_Renderer *renderer);
    ~Menu();

    void show();
    void showins();
    void showover();
    void handleEvents();
    int getState() {return state;}

    int state;

    int diff = NORMAL;

    bool ismusic = true;
    bool issound = true;

private:
    SDL_Color textcolor = {255, 255, 255, 255};

    SDL_Renderer *renderer;

    SDL_Texture *logo;

    SDL_Texture *playButton;
    SDL_Texture *redplayButton;

    SDL_Texture *instructionsButton;
    SDL_Texture *redinstructionsButton;

    SDL_Texture *backbutton;
    SDL_Texture *redbackbutton;

    SDL_Texture *nextbutton;
    SDL_Texture *rednextbutton;

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

    SDL_Texture *menuButton;
    SDL_Texture *redmenuButton;

    SDL_Texture *menuBack;

    void loadTextures();
    void freeTextures();

    Text* gameover;

    Text* instructions;
    Text* moveRL;
    Text* rotateblock;
    Text* softdrop;
    Text* harddrop;
    Text* pause_play;
    Text* instant_quit;

    Text* choosediff;
    Text* descrip;


    MixerManager* buttonclick;
};

#endif // MENU_H
