#include "game.h"

int cmGame::init(void)
{
    return 0;
}

void cmGame::run(void)
{
    init();
    
    while(1) {
        // Input functions
        
        if(newFrame()) {
            // Processing functions
            
            // Drawing functions
            mDraw->draw();
        }
    }
    
    return;
}
