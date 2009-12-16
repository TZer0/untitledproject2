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
        double life;
        int height;
        int width;
        cVector pos;
        cVector vel;
        cAnimation *animation;
        
        cEnemy(cEnemyData *data) {

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
        }
};

class cmEnemy : public cDataSystem, public tLoadingSystem<cEnemyData *> {
    private:
        std::list<cEnemy*> enemies;
        typedef std::list<std::string>::iterator Fileeater;

    public:
        cmEnemy() {}
        void init(void);
        void level_init(void) {}
        int load(void);
        void process(double);
        void draw(void);
        void clear_data(void);
        class cEnemy *add(char *script, cVector pos);
        virtual ~cmEnemy() {}
};

#endif

