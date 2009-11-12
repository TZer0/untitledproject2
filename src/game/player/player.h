#ifndef PLAYER_H
#define PLAYER_H

#include "../misc/moduletemplate.h"
#include "../misc/vector.h"
#include "../misc/animation/anim.h"
#include "../weapon/weapon.h"

#define JUMP_LIFE 0.3

class cmPlayer : public cDataSystem {
    private:
        double gravity;
        int horSpeed;
        int jumpHeight;
        int height;
        int width;
        double jumpLife;
        cVector pos;
        cVector vel;
        bool flagLeft;
        bool flagRight;
        bool flagUp;
        bool flagDown;
        bool flagFire;
        bool left;
        bool shot;
        cAnimation *animation;
        cWeapon *weapon;
        
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
        virtual ~cmPlayer() {}
};

#endif

