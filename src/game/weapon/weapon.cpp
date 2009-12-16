#include "weapon.h"
#include "luaweapon.h"

using namespace std;

cWeapon *cmWeapon::add(const char *id, int ammo, bool ean) {
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

cWeapon::cWeapon(cWeaponData *data, int ammo, bool ean) {
    this->data = data;
    this->ammo = ammo;
    this->ean = ean;

    l = luaL_newstate();
    luaL_openlibs(l); 
    luaopen_weapon(l);

    lc.register_self(l, "weapon");
    lc.register_int("ammo", &this->ammo);
    if(luaL_dostring(l, data->script)) {
        LOGU(LERR, "Lua script error %s", lua_tostring(l, -1));
    }
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
        mGame->mWeapon->cur = this;
        // Call Lua function which adds bullet(s).
        // spawnBullet("data/bullet/test.lua", pos.x, pos.y, vel.x, vel.y);
        lua_getglobal(l, "fire");
        lua_pushnumber(l, pos.x);
        lua_pushnumber(l, pos.y);
        lua_pushnumber(l, vel.x);
        lua_pushnumber(l, vel.y);
        lua_pcall(l, 4, 0, 0);
        if (ammo > 0)
            --ammo;
    } else {
        LOGS(LDEBUG, "Out of ammo!");
    }
}
