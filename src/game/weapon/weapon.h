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
        int ammo; // Negative value gives infinite ammo.
        bool ean; // Enemy And Netherworld. Weapon hurts player if true.
        
    public:
        cWeapon(int ammoArg, bool eanArg) {
            ammo = ammoArg;
            ean = eanArg;
        }

        void fire(cVector pos, cVector vel);
};

class cmWeapon : public cDataSystem {
    private:
        std::list<cWeapon*> weapons;

    public:
        cmWeapon() {}
        void init(void) {}
        void level_init(void) {}
        int load(void) { return 0; }
        void process(double) {}
        void draw(void) {}
        void clear_data(void) {}
        class cWeapon *add(std::string, int, bool);
        virtual ~cmWeapon() {}
};

#endif

