#ifndef BULLET_H
#define BULLET_H

#include <list>
#include <string>

#include "../draw.h"
#include "../game.h"
#include "../misc/file.h"
#include "../misc/moduletemplate.h"
#include "../misc/vector.h"
#include "../misc/luautil.h"
#include "../misc/log.h"
#include "../lua.h"
#include "../animation/anim.h"

class cBullData {
    public:
};

class cmBullData : public tLoadingSystem<cBullData *> {
    public:
        cBullData *cBData;
};

class cBullet {

    private:
        // cVector pos;
        // cVector vel;
        const char *script;
        lua_State *l;
		cLuaClass lc;

    public:
        cBullet(const char *script, cVector pos, cVector vel) {
            this->pos = pos;
            this->vel = vel;
            this->script = script;

            l = luaL_newstate();
            luaL_openlibs(l); 
            /* TODO: Make animation type dynamic. */
            animation = mGame->mAnim->add("PLAYER");
            animation->setSequence("IDLE");
            
            // Hijacking some code for testing:
            // Registers the class to the LUA script, with the name "cls"
            lc.register_self(l, "cls");				
            // Registers a new variable to the class, of type double
            lc.register_double("x", &this->pos.x);	
            lc.register_double("y", &this->pos.y);
            // Registers a vector
            lc.register_vector("vel", &this->vel);	
            
            // Simple LUA script example, showcasing both reading and writing
            // to the registered variables.
            //
            // Vectors must be handled in a special way:
            // It isn't possible to access a vector by their individual
            // components ("cls.vel.x"),
            // but, as shown here, accessing and reading it is still possible,
            // although slightly different.
            // Sadly I don't think I can do anything about that, without
            // slowing the algorithm
            // down significantly.
            //
            // If desirable, it might be easier to just register all vector variables
            // as doubles, which probably will make scripting a little more intuitive.
            luaL_dostring(l, 	"cls.y = cls.y/2        \n"
								"cls.x = cls.x/2        \n"
								"a = cls.vel            \n"
								"cls.vel = {a[2],a[1]}	\n"
								"print(a[1])            \n"
								"print(a[2])            \n");
            LOGS(LDEBUG, "cls.x is %f", this->pos.x);
            LOGS(LDEBUG, "cls.y is %f", this->pos.y);
            LOGS(LDEBUG, "vel.x is %f", this->vel.x);
            LOGS(LDEBUG, "vel.y is %f", this->vel.y);
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
        class cBullet *add(const char *script, cVector pos, cVector vel);  
        virtual ~cmBullet() {}

        cmBullData *bullData;
};

#endif

