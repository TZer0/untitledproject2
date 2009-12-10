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

class cmWeaponData : public tLoadingSystem<cBulletData *> {
    public:
        cWeaponData *cWData;
};

class cWeapon {
    private:
        cWeaponData *data;
		cLuaClass lc;
        
    public:
        int ammo; // Negative value gives infinite ammo.
        bool ean; // Enemy And Netherworld. Weapon hurts player if true.
        lua_State *l;
        cWeaponData *data;

        cWeapon(cWeapponData *data, int ammo, bool ean) {
            this->data = data;
            this->ammo = ammo;
            this->ean = ean;

            // Register the class to the LUA script.
            lc.register_self(l, "weapon");
            lc.register_int("ammo", &this->ammo);
            // Simple LUA script example, showcasing both reading and writing
            // Run script
            if(luaL_dostring(l, data->script)) {
                LOGU(LERR, "Lua script error %s", lua_tostring(l, -1));
            }
        }
        
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

