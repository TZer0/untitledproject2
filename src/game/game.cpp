#include "game.h"
#include "draw.h"
#include "misc/timer.h"

void cmGame::run(void)
{
    double delta;
    
    // Initializing stuff
    init();
    
    while(1) {
        // Input functions
        
        if(mTimer->get_timer() > 0) {
            delta = mTimer->delta();
            
            // Processing functions
            
            // Drawing functions
            mDraw->draw();
        }
    }
    
    return;
}
