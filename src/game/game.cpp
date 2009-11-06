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

void cmGame::run(void)
{
    double delta;
    
    // Initializing stuff
    init();
    
    while(!key[KEY_ESC]) {
        // Input functions
        mIn->update();
        
        if(mTimer->get_timer() > 0) {
            delta = mTimer->delta();
            
            // Processing functions
            mPlayer->input();
            mPlayer->process(delta);
            
            // Drawing functions
            mPlayer->draw();
            mDraw->draw();
        }
    }
    
    return;
}
