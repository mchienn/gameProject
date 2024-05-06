#include "Menu.h"
#include "defs.h"
#include <iostream>

Menu::Menu(SDL_Renderer *renderer)
{
    state = MENU;
    this->renderer = renderer;
    loadTextures();
}

Menu::~Menu()
{
    freeTextures();
}

void Menu::loadTextures()
{
    playButton = IMG_LoadTexture(renderer,  "img/play.png");
    redplayButton = IMG_LoadTexture(renderer, "img/playred.png");

    logo = IMG_LoadTexture(renderer, "img/Logo.png");

    instructionsButton = IMG_LoadTexture(renderer, "img/instructions.png");
    redinstructionsButton = IMG_LoadTexture(renderer, "img/redinstructions.png");

    quitButton = IMG_LoadTexture(renderer, "img/quit.png");
    redquitButton  = IMG_LoadTexture (renderer, "img/quitred.png");

    menuBack = IMG_LoadTexture(renderer, "img/backgroundmenu.png");

    // MusicButton = IMG_LoadTexture (renderer, "music.png");
    // SoundButton = IMG_LoadTexture (renderer, "sound.png");

    muteMusicButton = IMG_LoadTexture(renderer, "img/mute_music.png");
    muteSoundButton = IMG_LoadTexture(renderer, "img/mute_sound.png");
}

void Menu::freeTextures()
{
    SDL_DestroyTexture(playButton);
    SDL_DestroyTexture(instructionsButton);
    SDL_DestroyTexture(muteMusicButton);
    SDL_DestroyTexture(muteSoundButton);
}

void Menu::show()
{

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, menuBack, NULL, NULL);

    SDL_Rect logorect = {155, 115, 290, 100};

    SDL_RenderCopy(renderer, logo, NULL, &logorect);

    // Render the buttons
    SDL_Rect rect;
    rect.x = 225;
    rect.w = 150;
    rect.h = 50;
    rect.y = 335;

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    {
        if (mouseX >= 225 && mouseX <= 225 + 150 &&
            mouseY >= 335 && mouseY <= 335 + 50)
                {
                    SDL_Rect redrect;
                    redrect.x = 225;
                    redrect.w = 150;
                    redrect.h = 50;
                    redrect.y = 335;
                    SDL_RenderCopy(renderer, redplayButton, NULL, &redrect);
                }
        else
        {
            SDL_RenderCopy(renderer, playButton, NULL, &rect);
        }

        if (mouseX >= 225 && mouseX <= 225 + 150 &&
            mouseY >= 435 && mouseY <= 435 + 50)
        {
                    SDL_Rect redrect;
                    redrect.x = 225;
                    redrect.w = 150;
                    redrect.h = 50;
                    redrect.y = 435;
                    SDL_RenderCopy(renderer, redinstructionsButton, NULL, &redrect);
        }
        else
        {
            SDL_Rect ins = rect;
            ins.y += 100;
            SDL_RenderCopy(renderer, instructionsButton, NULL, &ins);
        }

        if (mouseX >= 225 && mouseX <= 225 + 150 &&
            mouseY >= 535 && mouseY <= 535 + 50)
            {
                    SDL_Rect redrect;
                    redrect.x = 225;
                    redrect.w = 150;
                    redrect.h = 50;
                    redrect.y = 535;
                    SDL_RenderCopy(renderer, redquitButton, NULL, &redrect);
            }
        else
        {
            SDL_Rect quit = rect;
            quit.y += 200;
            SDL_RenderCopy(renderer, quitButton, NULL, &quit);
        }

    }



    SDL_RenderPresent(renderer);
}

void Menu::handleEvents()
{


    SDL_Event event;
    while (SDL_PollEvent(&event))
        // Handle button clicks
        switch (event.type)
        {
        case (SDL_MOUSEBUTTONDOWN):
            int x = event.button.x;
            int y = event.button.y;
            // Check if the click was within the play button area
            if (x >= 225 && x <= 225 + 150 &&
                y >= 335 && y <= 335 + 50)
            {
                // handle play button click
                state = PLAY;
            }
            // Check if the click was within the instructions button area
            if (x >= 225 && x <= 225 + 150 &&
                y >= 435 && y <= 435 + 50)
            {
                // handle instructions button click
            }
            break;
        }
}
