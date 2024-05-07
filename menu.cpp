#include "Menu.h"
#include "defs.h"
#include <iostream>

Menu::Menu(SDL_Renderer *renderer)
{
    state = MENU;
    this->renderer = renderer;
    loadTextures();
    instructions = new Text(renderer, "img//font/gomarice_mix_bit_font.ttf",  LargeText, "        Instructions", textcolor);
    moveRL = new Text(renderer, "img/font/gomarice_mix_bit_font.ttf",        SmallText, "Move Left/Right:      Left/Right Arrow", textcolor);
    rotateblock = new Text(renderer, "img/font/gomarice_mix_bit_font.ttf",   SmallText, "Rotate:                            Z ", textcolor);
    softdrop = new Text(renderer, "img/font/gomarice_mix_bit_font.ttf",      SmallText, "Soft Drop:                     Down Arrow", textcolor);
    harddrop = new Text(renderer, "img/font/gomarice_mix_bit_font.ttf",      SmallText, "Hard Drop:                     Space", textcolor);
    pause_play = new Text(renderer, "img/font/gomarice_mix_bit_font.ttf",    SmallText, "Pause/Play:                  P", textcolor);
    instant_quit = new Text(renderer, "img/font/gomarice_mix_bit_font.ttf",  SmallText, "Instant quit:               ESC", textcolor);
}

Menu::~Menu()
{
    freeTextures();
}

void Menu::loadTextures()
{
    playButton = IMG_LoadTexture(renderer, "img/play.png");
    redplayButton = IMG_LoadTexture(renderer, "img/playred.png");

    logo = IMG_LoadTexture(renderer, "img/Logo.png");

    instructionsButton = IMG_LoadTexture(renderer, "img/instructions.png");
    redinstructionsButton = IMG_LoadTexture(renderer, "img/redinstructions.png");

    quitButton = IMG_LoadTexture(renderer, "img/quit.png");
    redquitButton = IMG_LoadTexture(renderer, "img/quitred.png");

    backbutton = IMG_LoadTexture(renderer, "img/back.png");
    redbackbutton = IMG_LoadTexture(renderer, "img/redback.png");

    menuBack = IMG_LoadTexture(renderer, "img/backgroundmenu.png");

    musicButton = IMG_LoadTexture (renderer, "img/music.png");
    redmusicButton = IMG_LoadTexture (renderer, "img/redmusic.png");

    soundButton = IMG_LoadTexture (renderer, "img/sound.png");
    redsoundButton = IMG_LoadTexture (renderer, "img/redsound.png");

    muteMusicButton = IMG_LoadTexture(renderer, "img/mute_music.png");
    redmuteMusicButton = IMG_LoadTexture (renderer, "IMG/redmute_music.png");

    muteSoundButton = IMG_LoadTexture(renderer, "img/mute_sound.png");
    redmuteSoundButton = IMG_LoadTexture (renderer, "img/redmute_sound.png");

    if (musicButton == NULL)
    {
        SDL_Log ("Error music \%s", SDL_GetError());
    }
}

void Menu::freeTextures()
{
    SDL_DestroyTexture(playButton);
    SDL_DestroyTexture(instructionsButton);
    SDL_DestroyTexture(muteMusicButton);
    SDL_DestroyTexture(muteSoundButton);
    SDL_DestroyTexture(redplayButton);
    SDL_DestroyTexture(redinstructionsButton);
    SDL_DestroyTexture(backbutton);
    SDL_DestroyTexture(redbackbutton);
}

void Menu::showins()
{
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, menuBack, NULL, NULL);

    SDL_Rect rect = {SmallMargin, LargeMargin, SquareButtonW, SquareButtonH};

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (mouseX >= SmallMargin && mouseX <= SmallMargin + SquareButtonW &&
        mouseY >= LargeMargin && mouseY <= LargeMargin + SquareButtonH)
    {
        SDL_RenderCopy(renderer, redbackbutton, NULL, &rect);
    }
    else
    {
        SDL_RenderCopy(renderer, backbutton, NULL, &rect);
    }

    instructions->display(SmallMargin, 175, renderer);

    moveRL->display(SmallMargin, 300, renderer);

    rotateblock->display(SmallMargin, 350, renderer);

    softdrop->display(SmallMargin, 400, renderer);

    harddrop->display(SmallMargin, 450, renderer);

    pause_play->display(SmallMargin, 500, renderer);

    instant_quit->display(SmallMargin, 550, renderer);

    SDL_RenderPresent(renderer);
}

void Menu::show()
{

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, menuBack, NULL, NULL);

    SDL_Rect logorect = {LargeMargin, LargeMargin, 290, 100};

    SDL_RenderCopy(renderer, logo, NULL, &logorect);

    // Render the buttons
    SDL_Rect rect  = {225, 335, RectButtonW, RectButtonH};
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    {
        if (mouseX >= 225 && mouseX <= 225 + RectButtonW &&
            mouseY >= 335 && mouseY <= 335 + RectButtonH)
        {
            SDL_Rect redrect = {225, 335, RectButtonW, RectButtonH};
            SDL_RenderCopy(renderer, redplayButton, NULL, &redrect);
        }
        else
        {
            SDL_RenderCopy(renderer, playButton, NULL, &rect);
        }

        if (mouseX >= 225 && mouseX <= 225 + RectButtonW &&
            mouseY >= 435 && mouseY <= 435 + RectButtonH)
        {
            SDL_Rect redrect = {225, 435, RectButtonW, RectButtonH};
            SDL_RenderCopy(renderer, redinstructionsButton, NULL, &redrect);
        }
        else
        {
            SDL_Rect ins = rect;
            ins.y += 100;
            SDL_RenderCopy(renderer, instructionsButton, NULL, &ins);
        }

        if (mouseX >= 225 && mouseX <= 225 + RectButtonW &&
            mouseY >= 535 && mouseY <= 535 + RectButtonH)
        {
            SDL_Rect redrect = {225, 535, RectButtonW, RectButtonH};
            SDL_RenderCopy(renderer, redquitButton, NULL, &redrect);
        }
        else
        {
            SDL_Rect quit = rect;
            quit.y += 200;
            SDL_RenderCopy(renderer, quitButton, NULL, &quit);
        }

        //music button
        SDL_Rect music = {500, 750, SquareButtonW, SquareButtonH};
        if (ismusic == true)
        {
            if (mouseX >= 500 && mouseX <= 500 + SquareButtonW &&
                mouseY >= 750 && mouseY <= 750 + SquareButtonH)
            {
                SDL_RenderCopy(renderer, redmusicButton, NULL, &music);
            }
            else
            {
                SDL_RenderCopy(renderer, musicButton, NULL, &music);
            }
        }
        else
        {
            if (mouseX >= 500 && mouseX <= 500 + SquareButtonW &&
                mouseY >= 750 && mouseY <= 750 + SquareButtonH)
            {
                SDL_RenderCopy(renderer, redmuteMusicButton, NULL, &music);
            }
            else
            {
                SDL_RenderCopy(renderer, muteMusicButton, NULL, &music);
            }
        }

        //soundbutton
        SDL_Rect sound = {500, 825, SquareButtonW, SquareButtonH};
        if (issound == true)
        {
            if (mouseX >= 500 && mouseX <= 500 + SquareButtonW &&
                mouseY >= 825 && mouseY <= 825 + SquareButtonH)
            {
                SDL_RenderCopy(renderer, redsoundButton, NULL, &sound);
            }
            else
            {
                SDL_RenderCopy(renderer, soundButton, NULL, &sound);
            }
        }
        else
        {
            if (mouseX >= 500 && mouseX <= 500 + SquareButtonW &&
                mouseY >= 825 && mouseY <= 825 + SquareButtonH)
            {
                SDL_RenderCopy(renderer, redmuteSoundButton, NULL, &sound);
            }
            else
            {
                SDL_RenderCopy(renderer, muteSoundButton, NULL, &sound);
            }
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
            if (state == MENU)
            {

                if (x >= 225 && x <= 225 + RectButtonW &&
                    y >= 335 && y <= 335 + RectButtonH)
                {
                    state = PLAY;
                }


                if (x >= 225 && x <= 225 + RectButtonW &&
                    y >= 435 && y <= 435 + RectButtonH)
                {
                    state = INSTRUCTIONS;
                }

                if (x >= 225 && x <= 225 + RectButtonW &&
                    y >= 535 && y <= 535 + RectButtonH)
                {
                    SDL_Quit();
                }

                if (x >= 500 && x <= 500 + SquareButtonW &&
                    y >= 750 && y <= 750 + SquareButtonH)
                {
                    ismusic = (ismusic ==  true ? false :true);
                }
                if (x >= 500 && x <= 500 + SquareButtonW &&
                    y >= 825 && y <= 825 + SquareButtonH)
                {
                    issound = (issound == true ? false : true);
                }
            }
            else if (state == INSTRUCTIONS)
            {
                if (x >= SmallMargin && x <= SmallMargin + SquareButtonW &&
                    y >= LargeMargin && y <= LargeMargin + SquareButtonH)
                {
                    state = MENU;
                }
            }

            break;
        }
}
