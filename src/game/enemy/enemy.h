#ifndef ENEMY_H
#define ENEMY_H

#include <list>
#include <string>
#include <map>

#include "../bullet/bullet.h"
#include "../game.h"
#include "../misc/file.h"
#include "../misc/moduletemplate.h"
#include "../misc/vector.h"
#include "../lua.h"
#include "../animation/anim.h"
#include "../weapon/weapon.h"

class cEnemyData {

    public:
        char *script;

};

class cEnemy {

    private:
        cWeapon *weapon;
        cEnemyData *data;
        lua_State *l;

    public:

        cAnimation *animation;
        
        cEnemy(cEnemyData *data) {

            l = luaL_newstate();
            luaL_openlibs(l);

            this->data = data;

            animation = mGame->mAnim->add("PLAYER");
            animation->setSequence("IDLE");

            // Give the enemy a weapon.
            LOGS(LDEBUG, "Adding %s...", "enemy weapon");
            weapon = mGame->mWeapon->add("print(1)\n", -1, false);
            LOGS(LDEBUG, "Weapon pointer: %p.", weapon);
            LOGS(LDEBUG, "Added %s...", "enemy weapon");

        }
};

class cmEnemy : public cDataSystem {
    private:
        std::list<cEnemy*> enemies;
        std::map<std::string, cEnemyData*> datas;

    public:
        cmEnemy() {}
        void init(void);
        void level_init(void) {}
        int load(void) { return 0; }
        void process(double) {}
        void draw(void) {}
        void clear_data(void);
        class cEnemy *add(char *script);
        virtual ~cmEnemy() {}
};

#endif

