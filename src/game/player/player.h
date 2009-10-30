#ifndef PLAYER_H
#define PLAYER_H

#include "../misc/moduletemplate.h"
#include "../misc/vector.h"

class cmPlayer : public cDataSystem {
    private:
        cVector pos;
        cVector vel;
        
    public:
        void init();
        void level_init() {}
        int load() {}
        void input();
        void process(double delta);
        void draw();
        void clear_data();
}

#endif
