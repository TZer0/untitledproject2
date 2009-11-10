#ifndef BULLET_H
#define BULLET_H

#include <list>
#include <string>

#include "../game.h"
#include "../misc/file.h"
#include "../misc/moduletemplate.h"
#include "../misc/vector.h"
#include "../lua.h"

class cBullet {

    private:
        cVector pos;
        cVector vel;
        char *script;
        lua_State *l;
        cAnimation *animation;

    public:
        cBullet(char *script, cVector pos, cVector vel) {
            this->pos = pos;
            this->vel = vel;
            this->script = script;

            l = luaL_newstate();
            luaL_openlibs(l); 
            /* TODO: Make animation type dynamic. */
            animation = mGame->mAnim->add("PLAYER");
            animation->setSequence("IDLE");
        }
};

class cmBullet : public cDataSystem {
    private:
        std::list<cBullet*> bullets;
        
    public:
        cmBullet() {}
        void init(void){}
        void level_init(void) {}
        int load(void) {return 0;}
        void process(double) {}
        void draw(void){}
        void clear_data(void) {}
        class cBullet *add(char *script, cVector pos, cVector vel);  
        virtual ~cmBullet() {}
};

#endif

