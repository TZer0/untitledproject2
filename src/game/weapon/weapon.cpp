#include "weapon.h"
#include "../game.h"

using namespace std;

class cWeapon *cmWeapon::add(string script, int ammo, bool ean) {
    LOGS(LDEBUG, "Adding weapon \"%s\"", script.c_str());
    class cWeapon *newWeapon;
    newWeapon = new cWeapon(ammo, ean);
    weapons.push_back(newWeapon);
    return newWeapon;
}

void cWeapon::fire(cVector pos, cVector vel) {
    if (ammo != 0) {
        LOGS(LDEBUG, "%s", "Bang!");
        if (ammo > 0)
            --ammo;
    } else {
        LOGS(LDEBUG, "%s", "Out of ammo!");
    }
}
