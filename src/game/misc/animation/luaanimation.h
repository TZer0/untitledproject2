#ifndef LUAANIMATION_H
#define LUAANIMATION_H

extern "C" {
#include <lua5.1/lua.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lualib.h>
}

void luaanim_open(lua_State *l);

#endif
