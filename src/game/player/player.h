#ifndef PLAYER_H
#define PLAYER_H

#include "../misc/moduletemplate.h"
#include "../collision/collision.h"
#include "../collision/colapply.h"
#include "../misc/vector.h"
#include "../animation/anim.h"
#include "../weapon/weapon.h"

#define JUMP_LIFE 0.3
#define MOD_PLAYER 9001

class cmPlayer : public cDataSystem, public cApplyCollision {
    private:
        double gravity;
        int horSpeed;
        int jumpHeight;
        int height;
        int width;
        double jumpLife;
        bool flagLeft;
        bool flagRight;
        bool flagUp;
        bool flagDown;
        bool flagFire;
        bool left;
        cAnimation *animation;
        cWeapon *weapon;
        cCollision *col;
        
    public:
        cVector pos;
        cVector vel;
        cmPlayer() : cApplyCollision(MOD_PLAYER, 1, 1.0,1.0)
            { }
        
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
        
        // Collision functions
        void collision_function(int caller_id, void* inst) {}
        bool test_collision(int dial_id, cCollision *target);
};

#endif

