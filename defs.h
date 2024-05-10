#ifndef _DEFS_H
#define _DEFS_H

#define ScreenW 600
#define ScreenH 900

#define BlockW 36
#define BlockH 36

#define Lines 20
#define Cols 10

#define BLOCKS 7
#define ROTATE 4

#define BoardW 4
#define BoardH 2

#define ExtraLargeText 70
#define LargeText 40
#define SmallText 23

#define RectButtonW 150
#define RectButtonH 50
#define SquareButtonW 50
#define SquareButtonH 50

#define SmallMargin 50
#define LargeMargin 115

#define Render_BlockW 32
#define Render_BlockH 32

// const std::string font_path = "font/gomarice_mix_bit_font.ttf";

enum STATES
{
    ACESS,
    MENU,
    PLAY,
    INSTRUCTIONS,
    GAMEOVER,
    ALL
};

enum DIFFICULTY
{
    NONE,
    NORMAL,
    HARD,
    MINDBLOW
};

#endif // _DEFS_H
