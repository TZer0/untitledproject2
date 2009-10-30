#include "misc/timer.h"
#include "misc/input.h"
#include "misc/file.h"
#include "player/player.h"
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
    
    // Setting working directory
    mFile->set_data_directory("data");
    
    // Logging intialization
    mLog.init(LDEBUG);
    
    // Module creation
    mDraw = new cmDraw;
    mTimer = new cmTimer;
    mIn = new cmInput;
    mPlayer = new cmPlayer;
    
    // Module initialization
    mDraw->init();
    mTimer->init();
    mPlayer->init();
    return 0;
}
