#include "weapon.h"

using namespace std;

class cWeapon *cmWeapon::add(char *script, int ammo, bool ean) {
    class cWeapon *newWeapon;
    newWeapon = new cWeapon(script, ammo, ean);
    weapons.push_back(newWeapon);
    return newWeapon;
}

void cmWeapon::clear_data() {
    // Delete cWeapon instances.
}

void cWeapon::fire(cVector pos, cVector vel) {
    if (ammo != 0) {
        luaL_dostring(l, script);
        if (ammo > 0)
            --ammo;
    } else {
        LOGS(LDEBUG, "Out of ammo!");
    }
}
