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

void luaconst_wapi(lua_State* L) {
    /* Windows messages */
    lua_pushinteger(L, WM_HOTKEY);
    lua_setglobal(L, "WM_HOTKEY");

    /* The modifiers of hotkey */
    lua_pushinteger(L, MOD_ALT);
    lua_setglobal(L, "MOD_ALT");

    lua_pushinteger(L, MOD_CONTROL);
    lua_setglobal(L, "MOD_CONTROL");

    lua_pushinteger(L, MOD_SHIFT);
    lua_setglobal(L, "MOD_SHIFT");

    lua_pushinteger(L, MOD_LEFT);
    lua_setglobal(L, "MOD_LEFT");

    lua_pushinteger(L, MOD_RIGHT);
    lua_setglobal(L, "MOD_RIGHT");

    lua_pushinteger(L, MOD_ON_KEYUP);
    lua_setglobal(L, "MOD_ON_KEYUP");

    lua_pushinteger(L, MOD_IGNORE_ALL_MODIFIER);
    lua_setglobal(L, "MOD_IGNORE_ALL_MODIFIER");
}