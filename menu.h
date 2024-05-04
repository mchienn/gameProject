// Menu.h
#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>

class Menu
{
public:
    Menu(SDL_Renderer *renderer);
    ~Menu();

    void show();
    void handleEvents();
    int getState() {return state;}

private:
    int state;
    SDL_Renderer *renderer;
    SDL_Texture *playButton;
    SDL_Texture *instructionsButton;
    SDL_Texture *muteMusicButton;
    SDL_Texture *muteSoundButton;
    SDL_Texture *menuBack;

    void loadTextures();
    void freeTextures();
};

#endif // MENU_H
