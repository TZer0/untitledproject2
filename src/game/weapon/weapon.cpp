#include "weapon.h"

using namespace std;

class cWeapon *cmWeapon::add(const char *script, int ammo, bool ean) {
    class cWeapon *newWeapon;
    newWeapon = new cWeapon(script, ammo, ean);
    weapons.push_back(newWeapon);
    return newWeapon;
}

void cmWeapon::clear_data() {
}

int cmWeapon::load(void) {
    for (list<string>::iterator i = scripts.begin(); i != scripts.end(); ++i) {
        scripts = mGame->mFile->dirRecursiveGet("weapons", "lua");
    }
    return 0;
}

void cWeapon::fire(cVector pos, cVector vel) {
    if (ammo != 0) {
        // Call Lua function which adds bullet(s).
        if (ammo > 0)
            --ammo;
    } else {
        LOGS(LDEBUG, "Out of ammo!");
    }
}
