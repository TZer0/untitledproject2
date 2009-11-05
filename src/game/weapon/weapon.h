#ifndef WEAPON_H
#define WEAPON_H

#include "../misc/moduletemplate.h"
#include "../misc/vector.h"
#include "../../lua.h"

void luaanim_open(lua_State *l);

class cmWeapon: public cDataSystem {
    private:
        int ammo;
        bool ean;
        
    public:
        void fire(cVector pos, cVector vel)
        void level_init() {}
        
        int load() {
            return 0;
        }
        
        void init();
        void input();
        void process(double delta);
        void draw();
        void clear_data();
};

#endif
