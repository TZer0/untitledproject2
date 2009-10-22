#ifndef GAME_H
#define GAME_H

// Forward declarations of modules
class cmDraw;

// Misc modules
class cmTimer;

class cmGame {
    public:
        int init(void);
        void run(void);
        
        // Modules
        class cmDraw *mDraw;

        // Misc modules
        class cmTimer *mTimer;
};

extern class cmGame *mGame;

#endif
