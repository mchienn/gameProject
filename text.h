#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Text
{
public:
    Text(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);
    void display(int x, int y, SDL_Renderer *renderer);
    static SDL_Texture *loadFont(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &message_text, const SDL_Color &color);
    SDL_Texture *_message;
    SDL_Rect _message_rect;

};

#endif // TEXT_H
