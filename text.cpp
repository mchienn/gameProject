#include "text.h"

Text::Text(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color)
{
    if (TTF_Init() == -1)
    {
        SDL_Log("Error init TTF \%s", SDL_GetError());
    }
    else
    {
        _message = loadFont(renderer, font_path, font_size, message_text, color);
        SDL_QueryTexture(_message, nullptr, nullptr, &_message_rect.w, &_message_rect.h);
    }
}

void Text::display(int x, int y, SDL_Renderer *renderer)
{
    _message_rect.x = x;
    _message_rect.y = y;
    SDL_RenderCopy(renderer, _message, nullptr, &_message_rect);
}

SDL_Texture *Text::loadFont(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color)
{
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
    if (!font)
    {
        SDL_Log("Error \%s", SDL_GetError());
    }
    SDL_Surface *surface = TTF_RenderText_Blended(font, message_text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return texture;
}

void Text::update(SDL_Renderer *renderer, const std::string &new_message, const std::string &font_path, int font_size, const SDL_Color &color)
{
    SDL_DestroyTexture(_message);
    _message = loadFont(renderer, font_path, font_size, new_message, color);
    SDL_QueryTexture(_message, nullptr, nullptr, &_message_rect.w, &_message_rect.h);
}
