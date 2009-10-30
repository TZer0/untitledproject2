#ifndef PLAYER_H
#define PLAYER_H

#include "../misc/moduletemplate.h"
#include "../misc/vector.h"

#define HOR_SPEED   100.0

class cmPlayer : public cDataSystem {
    private:
        double gravity;
        cVector pos;
        cVector vel;
        bool flagLeft;
        bool flagRight;
        bool flagUp;
        bool flagDown;
        
    public:
        void level_init() {}
        
        int load() {
            return 0;
        }
        
        void init();
        void input();
        void process(double delta);
        void draw();
        void clear_data();
};

#endif
