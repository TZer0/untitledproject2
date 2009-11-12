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
        void load(void);
        int init(void);
        void run(void);

        // Modules
        class cmDraw *mDraw;
        class cmPlayer *mPlayer;
        class cmLevel *mLevel;
        class cmWeapon *mWeapon;
        class cmEnemy *mEnemy;
        class cmBullet *mBullet;
        // Misc modules
        class cmTimer *mTimer;
        class cmInput *mIn;
        class cmFile *mFile;
        class cmAnim *mAnim;
        class cmSound *mSound;
};

extern class cmGame *mGame;

#endif

