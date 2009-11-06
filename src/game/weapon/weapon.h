#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <list>

#include "../misc/moduletemplate.h"
#include "../misc/vector.h"
#include "../lua.h"

// void luaanim_open(lua_State *l);

class cWeapon {
    private:
        int ammo;
        bool ean;
        
    public:
        cWeapon() {
            ammo = 10;
            ean = false;
        }

        void fire(cVector pos, cVector vel);
};

class cmWeapon : public cDataSystem {
    private:
        // Lists of weapons.
        std::list<cWeapon*> weapons;

    public:
        cmWeapon() {}
        void init(void) {}
        void level_init(void) {}
        int load(void) { return 0; }
        void process(double) {}
        void draw(void) {}
        void clear_data(void) {}
        class cWeapon *add(std::string);
        virtual ~cmWeapon() {}
};

#endif

