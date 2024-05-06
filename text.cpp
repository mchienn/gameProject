/*#include "text.h"

Text::Text(SDL_Renderer* renderer, std::string& font_path, int font_size, std::string& message_text, SDL_Color& color)
{
    _message = loadFont(renderer, font_path, font_size, message_text, color);
    SDL_QueryTexture(_message, nullptr, nullptr, &_message_rect.w, &_message_rect.h);
}

void Text::display(int x, int y, SDL_Renderer* renderer)
{
    _message_rect.x = x;
    _message_rect.y = y;
    SDL_RenderCopy(renderer, _message, nullptr, &_message_rect);
}

SDL_Texture* Text::loadFont(SDL_Renderer* renderer, std::string& font_path, int font_size, std::string& message_text, SDL_Color& color)
{
    TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
    auto message_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
    auto message_texture = SDL_CreateTextureFromSurface(renderer, message_surface);
    SDL_FreeSurface(message_surface);
    TTF_CloseFont(font);
    return message_texture;
}

Text::~Text()
{
    SDL_DestroyTexture(_message);
}*/
