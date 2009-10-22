#include "misc/timer.h"
#include "misc/input.h"
#include "game.h"
#include "draw.h"
int cmGame::init(void)
{
    // Initialize allegro
    allegro_init();
    
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800,600, 0,0);
    
    install_keyboard();
    install_mouse();
    
    mDraw = new cmDraw;
    mTimer = new cmTimer;
    mIn = new cmInput;

    mDraw->init();
    mTimer->init();
    return 0;
}
