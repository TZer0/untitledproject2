#ifndef BULLET_H
#define BULLET_H

#include <list>
#include <string>

#include "../draw.h"
#include "../game.h"
#include "../misc/file.h"
#include "../misc/moduletemplate.h"
#include "../misc/vector.h"
#include "../lua.h"
#include "../animation/anim.h"

class cBullData {
    public:
};

class cmBullData : public tLoadingSystem<cBullData *> {
    public:
        cBullData *bullData;
};

class cBullet {

    private:
        // cVector pos;
        // cVector vel;
        char *script;
        lua_State *l;


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
        cAnimation *animation;
        cVector pos;
        cVector vel;
};

class cmBullet : public cDataSystem {
    private:
        std::list<cBullet*> bullets;
        typedef std::list<cBullet*>::iterator EatBullets;

    public:
        cmBullet() {
            bullData = new cmBullData;
        }
        void init(void){}
        void level_init(void) {}
        int load(void); 
        void process(double); 
        void draw(void);
        void clear_data(void);
        class cBullet *add(char *script, cVector pos, cVector vel);  
        virtual ~cmBullet() {}

        cmBullData *bullData;
};

#endif

