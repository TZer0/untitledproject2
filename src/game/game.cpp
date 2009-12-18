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
#include "animation/anim.h"

#define MAX_DELTA 0.1
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

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
            double delta_left = delta;

            // Processing functions
            mPlayer->input();

            while (delta_left > 0){
                double dist = min(delta_left, MAX_DELTA);
                delta_left -= dist;

                mPlayer->process(dist);
                mEnemy->process(dist);
                mBullet->process(dist);
            }
            mAnim->process(delta);

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
