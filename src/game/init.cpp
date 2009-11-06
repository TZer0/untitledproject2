#include "misc/timer.h"
#include "misc/input.h"
#include "misc/file.h"
#include "misc/animation/anim.h"
#include "player/player.h"
#include "level/level.h"
#include "weapon/weapon.h"
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
    mFile = new cmFile;
    mFile->set_data_directory("data");
    
    // Logging intialization
    mLog.init(LDEBUG);
    
    // Module creation
    mDraw = new cmDraw;
    mTimer = new cmTimer;
    mIn = new cmInput;
    mPlayer = new cmPlayer;
    mAnim = new cmAnim;
    mLevel = new cmLevel;
    mWeapon = new cmWeapon;
    
    // Loading stuff
    load();
    
    // Module initialization
    LOGS(LDEBUG, "Initializing %s...", "mDraw");
    mDraw->init();
    LOGS(LDEBUG, "Initializing %s...", "mTimer");
    mTimer->init();
    LOGS(LDEBUG, "Initializing %s...", "mPlayer");
    mPlayer->init();
    LOGS(LDEBUG, "Initializing %s...", "mAnim");
    mAnim->init();
    LOGS(LDEBUG, "Initializing %s...", "mLevel");
    mLevel->init();
    LOGS(LDEBUG, "Initializing %s...", "mWeapon");
    mWeapon->init();
    
    return 0;
}
