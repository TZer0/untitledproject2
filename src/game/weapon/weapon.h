#ifndef WEAPON_H
#define WEAPON_H

#include <list>
#include <string>

#include "../bullet/bullet.h"
#include "../game.h"
#include "../misc/file.h"
#include "../misc/moduletemplate.h"
#include "../misc/vector.h"
#include "../lua.h"

class cWeapon {
    private:
        int ammo; // Negative value gives infinite ammo.
        bool ean; // Enemy And Netherworld. Weapon hurts player if true.
        lua_State *l;
        
    public:
        cWeapon(const char *script, int ammo, bool ean) {
            this->ammo = ammo;
            this->ean = ean;

            l = luaL_newstate();
            luaL_openlibs(l);
            luaL_dostring(l, script);
        }

        void fire(cVector pos, cVector vel);
};

class cmWeapon : public cDataSystem {
    private:
        std::list<cWeapon*> weapons;
        std::list<std::string> scripts;

    public:
        cmWeapon() {}
        void init(void) {}
        void level_init(void) {}
        int load(void);
        void process(double) {}
        void draw(void) {}
        void clear_data(void);
        class cWeapon *add(const char *id, int ammo, bool ean);
        virtual ~cmWeapon() {}
};

#endif

