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
#include "../collision/collision.h"
#include "../collision/colapply.h"
#include "../lua.h"
#include "../animation/anim.h"

#define MOD_BULLET 101

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
		cLuaClass lc;

    public:
        bool toDie;
        
        int life;
        cBullet(cBullData *data, cVector pos, cVector vel) {
            this->pos = pos;
            this->vel = vel;
            this->data= data;

            this->life = 0;
            
            toDie = false;

            l = luaL_newstate();
            luaL_openlibs(l); 
            /* TODO: Make animation type dynamic. */
            animation = mGame->mAnim->add("BULLET");
            animation->setSequence("IDLE");
            
            // Registers the class to the LUA script
            lc.register_self(l, "shot");
                lc.register_double("x", &this->pos.x);
                lc.register_double("y", &this->pos.y);
                lc.register_double("dx", &this->vel.x);
                lc.register_double("dy", &this->vel.y);
                lc.register_int("life", &this->life);
            // Simple LUA script example, showcasing both reading and writing
            // Run script
            if(luaL_dostring(l, data->script)) {
                LOGU(LERR, "Lua script error %s", lua_tostring(l, -1));
            }

        }
        
        lua_State *l;
        cAnimation *animation;
        cVector pos;
        cVector vel;
};

class cmBullet : public cDataSystem, public cApplyCollision, public tLoadingSystem<cBullData *> {
    private:
        std::list<cBullet*> bullets;
        typedef std::list<cBullet*>::iterator EatBullets;

    public:
        cmBullet() : cApplyCollision(MOD_BULLET, 1, 1.0,1.0) {
            bullData = new cmBullData;
        }
        
        void init(void) {
            col = mGame->mCollision->create(CollisionPoint, &colpoint, cVector(0,0));
        }
        
        void level_init(void) {}
        int load(void); 
        void process(double); 
        void draw(void);
        void clear_data(void);
        class cBullet *add(const char *script, cVector pos, cVector vel);  
        virtual ~cmBullet() {}
        
        cBullet *cur;
        
        cmBullData *bullData;
        cVector colpoint;
        cCollision *col;
        
        // Collision functions
        void collision_function(int caller_id, void* inst) {}
        bool test_collision(int dial_id, cCollision *target);
};

#endif

