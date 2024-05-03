// Menu.h
#ifndef MENU_H
#define MENU_H

#include <SDL.h>

class Menu {
public:
    Menu(SDL_Renderer* renderer);
    ~Menu();

    void show();
    void handleEvents(SDL_Event& event);

private:
    SDL_Renderer* renderer;
    SDL_Texture* playButton;
    SDL_Texture* instructionsButton;
    SDL_Texture* muteMusicButton;
    SDL_Texture* muteSoundButton;

    void loadTextures();
    void freeTextures();
};

#endif // MENU_H
