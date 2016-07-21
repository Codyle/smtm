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

#include <Windows.h>
#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>
#include <smtm/lwapilib.h>

static int wapi_FindWindow(lua_State* L) {
    const char* cname = luaL_optstring(L, 1, NULL);
    const char* wname = luaL_optstring(L, 2, NULL);

    if (cname == NULL && wname == NULL) {
        return luaL_argerror(L, 1, "class or windows name expected");
    }

    HWND hw = FindWindow(cname, wname);

    lua_pushinteger(L, (int)hw);

    return 1;
}

static const luaL_Reg wapilib[] = {
    { "FindWindow", wapi_FindWindow },
    { NULL, NULL }
};

LUAMOD_API int luaopen_wapi(lua_State* L) {
    luaL_newlib(L, wapilib);

    return 1;
}