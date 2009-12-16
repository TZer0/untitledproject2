#include "misc/timer.h"
#include "misc/input.h"
#include "misc/file.h"
#include "animation/anim.h"
#include "player/player.h"
#include "level/level.h"
#include "weapon/weapon.h"
#include "enemy/enemy.h"
#include "bullet/bullet.h"
#include "game.h"
#include "draw.h"
#include "sound/sound.h"


int cmGame::init(void)
{
    // Initialize allegro
    allegro_init();
    
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    
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
    mEnemy = new cmEnemy;
    mBullet = new cmBullet;
    mSound = new cmSound;
    mCollision = new cmCollision;

    // Loading stuff
    load();
    
    // Module initialization
    LOGS(LDEBUG, "Initializing mDraw...");
    mDraw->init();
    LOGS(LDEBUG, "Initializing mTimer...");
    mTimer->init();
    LOGS(LDEBUG, "Initializing mPlayer...");
    mPlayer->init();
    LOGS(LDEBUG, "Initializing mAnim...");
    mAnim->init();
    LOGS(LDEBUG, "Initializing mLevel...");
    mLevel->init();
    LOGS(LDEBUG, "Initializing mWeapon...");
    mWeapon->init();
    LOGS(LDEBUG, "Initializing mEnemy...");
    mEnemy->init();
    LOGS(LDEBUG, "Initializing mBullet...");
    mBullet->init();
    LOGS(LDEBUG, "Initializing mCollision...");
    mCollision->init();
  
    return 0;
}
