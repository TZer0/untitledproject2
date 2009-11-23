#ifndef BULLET_H
#define BULLET_H

#include <list>
#include <string>

#include "../draw.h"
#include "../game.h"
#include "../misc/file.h"
#include "../misc/moduletemplate.h"
#include "../misc/loadtemplate.h"
#include "../misc/vector.h"
#include "../misc/luautil.h"
#include "../misc/log.h"
#include "../lua.h"
#include "../animation/anim.h"

class cBullData {
    public:
        const char *script;
};

class cmBullData : public tLoadingSystem<cBullData *> {
    public:
        cBullData *cBData;
};

class cBullet {

    private:
        // cVector pos;
        // cVector vel;
        cBullData *data;
        lua_State *l;
		cLuaClass lc;

    public:
        int life;
        cBullet(cBullData *data, cVector pos, cVector vel) {
            this->pos = pos;
            this->vel = vel;
            this->data = data;

            this->life = 0;

            l = luaL_newstate();
            luaL_openlibs(l);
            
            /* TODO: Make animation type dynamic. */
            animation = mGame->mAnim->add("BULLET");
            animation->setSequence("FRAMEA");
            
            // Registers the class to the LUA script
            lc.register_self(l, "shot");
                lc.register_double("x", &this->pos.x);
                lc.register_double("y", &this->pos.y);
                
                lc.register_double("dx", &this->vel.x);
                lc.register_double("dy", &this->vel.y);
                
                lc.register_int("life", &this->life);
            
            // Run script
            if(luaL_dostring(l, data->script)) {
                LOGU(LERR, "Lua script error %s", lua_tostring(l, -1));
            }
        }
        cAnimation *animation;
        cVector pos;
        cVector vel;
};

class cmBullet : public cDataSystem, public tLoadingSystem<cBullData *> {
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
        class cBullet *add(const char *script, cVector pos, cVector vel);  
        virtual ~cmBullet() {}

        cmBullData *bullData;
};

#endif

