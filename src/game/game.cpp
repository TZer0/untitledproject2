/**
* File: game.cpp
*
* Description: Contains run(), the function that does it all.
*/
#include "port.h"
#include "game.h"
#include "draw.h"
#include "misc/timer.h"
#include "misc/input.h"
#include "player/player.h"
#include "level/level.h"
#include "weapon/weapon.h"
#include "enemy/enemy.h"
#include "bullet/bullet.h"

void cmGame::run(void)
{
    double delta;
    
    // Initializing stuff
    init();
    
    mTimer->reset_timer();
    while(!key[KEY_ESC] && !key[KEY_Q]) {
        // Input functions
        mIn->update();
        
        if(mTimer->get_timer() > 0) {
            delta = mTimer->delta();
            
            // Processing functions
            mPlayer->input();
            mPlayer->process(delta);
            mBullet->process(delta);

            // Drawing functions
            mEnemy->draw();
            mDraw->draw();
            mLevel->draw();
            mBullet->draw();
            mPlayer->draw();
        }
    }
    
    return;
}
