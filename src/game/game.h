#ifndef GAME_H
#define GAME_H

// Logging functions
#include "misc/log.h"

// Forward declarations of modules
class cmDraw;

// Misc modules
class cmTimer;
class cmInput;

class cmGame {
    public:
        int init(void);
        void run(void);
        
        // Modules
        class cmDraw *mDraw;
        class cmPlayer *mPlayer;

        // Misc modules
        class cmTimer *mTimer;
        class cmInput *mIn;
};

extern class cmGame *mGame;

#endif
