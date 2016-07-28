/*
 * Copyright (C) 2016 HE Yaowen <he.yaowen@hotmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <smtm/lsmtmlib.h>

static int smtm_udatatointeger(lua_State* L) {
    void* udata = lua_touserdata(L, 1);

    if (udata == NULL) {
        return luaL_argerror(L, 1, "argument is not a valid userdata");
    }

    lua_pushinteger(L, *((int*) udata));

    return 1;
}

static int smtm_udatatostring(lua_State* L) {
    void* udata = lua_touserdata(L, 1);

    if (udata == NULL) {
        return luaL_argerror(L, 1, "argument is not a valid userdata");
    }

    lua_pushstring(L, (char*) udata);

    return 1;
}

static int smtm_integertoudata(lua_State* L) {
    void* ud = lua_newuserdata(L, sizeof(int));
    *(int*)ud = lua_tointeger(L, 1);

    lua_pushlightuserdata(L, ud);
    return 1;
}

static int smtm_stringtoudata(lua_State* L) {
    const char* src = lua_tostring(L, 1);
    size_t s = strlen(src) + 1;
    void* ud = lua_newuserdata(L, s);

    strcpy_s((char*)ud, s, src);

    lua_pushlightuserdata(L, ud);
    return 1;
}

static const luaL_Reg smtmlib[] = {
    {"udatatointeger", smtm_udatatointeger},
    {"udatatostring", smtm_udatatostring},
    {"integertoudata", smtm_integertoudata},
    {"stringtoudata", smtm_stringtoudata},
	{NULL, NULL}
};

LUAMOD_API int luaopen_smtm(lua_State* L) {
    luaL_newlib(L, smtmlib);
    luaconst_smtm(L);

    return 1;
}