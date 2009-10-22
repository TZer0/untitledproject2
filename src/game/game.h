#ifndef GAME_H
#define GAME_H

// Forward declarations of modules
class cmDraw;

class cmGame {
    public:
        int init(void);
        void run(void);
        
        // Modules
        class cmDraw *mDraw;
};

extern class cmGame *mGame;

#endif
