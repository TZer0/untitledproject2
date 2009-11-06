#include "weapon.h"
#include "../game.h"

using namespace std;

class cWeapon *cmWeapon::add(string script) {
    LOGS(LDEBUG, "Adding weapon \"%s\"", script.c_str());
    class cWeapon *newWeapon;
    newWeapon = new cWeapon();
    weapons.push_back(newWeapon);
    return newWeapon;
}

void cWeapon::fire(cVector pos, cVector vel) {
    if (ammo > 0) {
    --ammo;
        LOGS(LDEBUG, "%s", "Bang!");
    } else {
        LOGS(LDEBUG, "%s", "Out of ammo!");
    }
}
