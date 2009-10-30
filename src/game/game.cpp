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
            
            // Drawing functions
            mDraw->draw();
        }
    }
    
    return;
}
