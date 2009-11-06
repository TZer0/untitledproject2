#ifndef ENEMY_H
#define ENEMY_H

#include "../misc/moduletemplate.h"
#include "../misc/vector.h"
#include "../misc/animation/anim.h"

class cmEnemy : public cDataSystem {
    private:
        int movementSpeed;
        cVector pos;
        cVector vel;
        cAnimation *animation;

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

