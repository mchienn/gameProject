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
    instructionsButton = IMG_LoadTexture(renderer, "img/instructions.png");

    // MusicButton = IMG_LoadTexture (renderer, "music.png");
    // SoundButton = IMG_LoadTexture (renderer, "sound.png");

    muteMusicButton = IMG_LoadTexture(renderer, "img/mute_music.png");
    muteSoundButton = IMG_LoadTexture(renderer, "img/mute_sound.png");

    // if (!playButton || !instructionsButton || !muteMusicButton || !muteSoundButton)
    //{
    //    std::cout << "Failed to load button images" << std::endl;
    // }
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
    // Render the buttons
    SDL_Rect rect;
    rect.x = 225; // the button width is the same as the screen width
    rect.w = 150;
    rect.h = 50;
    rect.y = 335;

    SDL_RenderCopy(renderer, playButton, NULL, &rect);

    // Instructions button
    rect.y += 100; // position it above the play button
    SDL_RenderCopy(renderer, instructionsButton, NULL, &rect);

    // Quit button
    rect.y = (960 - 200) / 2 + 250; // position it below the play button
    // SDL_RenderCopy(renderer, quitButton, NULL, &rect);

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
                y >= 355 && y <= 355 + 50)
            {
                // handle play button click
                state = PLAY;
            }
            // Check if the click was within the instructions button area
            if (x >= 225 && x <= 225 + 150 &&
                y >= 455 && y <= 455 + 50)
            {
                // handle instructions button click
            }
            break;
        }
}
