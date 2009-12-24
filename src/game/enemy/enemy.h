#ifndef ENEMY_H
#define ENEMY_H

#include <list>
#include <string>
#include <map> 
#include "../bullet/bullet.h"
#include "../player/player.h"
#include "../game.h"
#include "../misc/file.h"
#include "../misc/timer.h"
#include "../misc/moduletemplate.h"
#include "../misc/vector.h"
#include "../lua.h"
#include "../animation/anim.h"
#include "../weapon/weapon.h"
#include "../misc/loadtemplate.h"
#include "../collision/colapply.h"

#include "ai/ai.h"

#define MOD_ENEMY 0xBEAF

class cEnemyData {

    public:
        char *script;
};

class cEnemy {

    private:
        cEnemyData *data;
        lua_State *l;

    public:
        cWeapon *weapon;
        cAI *ai;		// The AI we use. Different AI types will use different cAI derived classes
        double life;
        int height;
        int width;
        cVector pos;
        cVector vel;
        cAnimation *animation;
        cCollision *col;
        sColSectorInstance *colsector;
        
        cEnemy(cEnemyData *data) : ai(NULL) {

            l = luaL_newstate();
            luaL_openlibs(l);

            this->data = data;
            this->life = 0;

            animation = mGame->mAnim->add("PLAYER");
            animation->setSequence("IDLE");

            // Give the enemy a weapon.
            LOGS(LDEBUG, "Adding %s...", "enemy weapon");
            weapon = mGame->mWeapon->add("data/weapons/bfg9k1.lua", -1, true);
            LOGS(LDEBUG, "Weapon pointer: %p.", weapon);
            LOGS(LDEBUG, "Added %s...", "enemy weapon");
            
            // Create a dummy collision object
            col = mGame->mCollision->create(CollisionRectangle, &pos, cVector(0,0), animation->getW(), animation->getH());
            
            // Create sector
            colsector = new sColSectorInstance(this);
        }
};

class cmEnemy : 
		public cDataSystem,
		public cApplyCollision,
		public tLoadingSystem<cEnemyData *>
{
    private:
        std::list<cEnemy*> enemies;
        typedef std::list<std::string>::iterator Fileeater;

    public:
		// Current enemy in processing
		cEnemy *cur;
		
        cmEnemy() : cApplyCollision(MOD_ENEMY, 5, 1,1) {}
        void init(void);
        void level_init(void) {}
        int load(void);
        void process(double);
        void draw(void);
        void clear_data(void);
        class cEnemy *add(char *script, cVector pos);
        virtual ~cmEnemy() {}
        
        // Collision functions
        void collision_function(int caller_id, void*inst);
        bool test_collision(int dial_id, cCollision *target);
};

#endif

