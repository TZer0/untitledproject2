#include "weapon.h"

using namespace std;

class cWeapon *cmWeapon::add(const char *id, int ammo, bool ean) {
    class cWeapon *newWeapon;
    newWeapon = new cWeapon(get(id), ammo, ean);
    weapons.push_back(newWeapon);
    return newWeapon;
}

void cmWeapon::clear_data() {
}

int cmWeapon::load(void) {
    filedb = mGame->mFile->dirRecursiveGet("weapons", "lua");
    for (list<string>::iterator i = filedb.begin(); i != filedb.end(); ++i) {
        cWeaponData *tmp = new cWeaponData;
        tmp->script = mGame->mFile->get_script((*i).c_str());
        LOGS(LDEBUG, "Loading weapon %s",
                mGame->mFile->execdir_strip((*i).c_str()).c_str());
        insert(mGame->mFile->execdir_strip((*i).c_str()), tmp);
    }
    return 0;
}

void cWeapon::spawnBullet(string id, double px, double py, double vx, double vy) {
    cVector pos, vel;

    pos.x = px;
    pos.y = py;
    vel.x = vx;
    vel.y = vy;
    mGame->mBullet->add(id.c_str(), pos, vel);
}

void cWeapon::fire(cVector pos, cVector vel) {
    if (ammo != 0) {
        // Call Lua function which adds bullet(s).
        spawnBullet("data/bullet/test.lua", pos.x, pos.y, vel.x, vel.y);
        lua_getglobal(l, "fire");
        lua_pcall(l, 0, 0, 0);
        if (ammo > 0)
            --ammo;
    } else {
        LOGS(LDEBUG, "Out of ammo!");
    }
}
