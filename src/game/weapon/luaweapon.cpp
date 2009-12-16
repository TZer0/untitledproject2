#include "luaweapon.h"
#include "weapon.h"

static int spawnBullet(lua_State *storS) {
    cWeapon* cur = mGame->mWeapon->cur;
    cur->spawnBullet(luaL_checkstring(storS, 1),
                luaL_checknumber(storS, 2),
                luaL_checknumber(storS, 3),
                luaL_checknumber(storS, 4),
                luaL_checknumber(storS, 5));
    return 0;
}

static struct luaL_Reg noe[] = {
    {"spawn", spawnBullet},
    NULL};

void luaopen_weapon(lua_State *storS) {
    luaL_register(storS, "_G", noe);
}
