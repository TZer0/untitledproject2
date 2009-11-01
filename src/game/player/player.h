#ifndef PLAYER_H
#define PLAYER_H

#include "../misc/moduletemplate.h"
#include "../misc/vector.h"

class cmPlayer : public cDataSystem {
    private:
        double gravity;
        int horSpeed;
        int jumpHeight;
        cVector pos;
        cVector vel;
        cVector acc;
        bool flagLeft;
        bool flagRight;
        bool flagUp;
        bool flagDown;
        bool inAir;
        
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
