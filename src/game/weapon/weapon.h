#ifndef WEAPON_H
#define WEAPON_H

#include <list>
#include <string>

#include "../bullet/bullet.h"
#include "../game.h"
#include "../misc/file.h"
#include "../misc/moduletemplate.h"
#include "../misc/loadtemplate.h"
#include "../misc/vector.h"
#include "../lua.h"

class cWeaponData {
    public:
        const char *script;
};

class cWeapon {
    private:
        cWeaponData *data;
		cLuaClass lc;
        
    public:
        int ammo; // Negative value gives infinite ammo.
        bool ean; // Enemy And Netherworld. Weapon hurts player if true.
        lua_State *l;

        cWeapon(cWeaponData *data, int ammo, bool ean);
        
        ~cWeapon() {
            lua_close(l);
        }

        void spawnBullet(std::string, double, double, double, double);
        void fire(cVector pos, cVector vel);
};

class cmWeapon: public cDataSystem, public tLoadingSystem<cWeaponData *> {
    private:
        std::list<cWeapon*> weapons;
        std::list<std::string> scripts;

    public:
        cmWeapon() {}
        cWeapon* cur;
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

