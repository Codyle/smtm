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

static int wapi_GetWindowThreadProcessId(lua_State* L) {
    DWORD pid;
    HWND hw = (HWND)luaL_optinteger(L, 1, 0);

    lua_pushinteger(L, GetWindowThreadProcessId(hw, &pid));
    lua_pushinteger(L, (int)pid);

    return 2;
}

static int wapi_OpenProcess(lua_State* L) {
    DWORD access = (DWORD)luaL_optinteger(L, 1, PROCESS_ALL_ACCESS);
    BOOL inherit = (BOOL)luaL_optinteger(L, 2, 0);
    DWORD pid = (DWORD)luaL_optinteger(L, 3, 0);
    HANDLE proc;

    proc = OpenProcess(access, inherit, pid);
    lua_pushinteger(L, (int)proc);

    return 1;
}

static int wapi_ReadProcessMemory(lua_State* L) {
    HANDLE proc = (HANDLE)luaL_optinteger(L, 1, 0);
    LPCVOID addr = (LPCVOID)luaL_optinteger(L, 2, 0);
    SIZE_T len = (SIZE_T)luaL_optinteger(L, 3, 1);
    void* buff = lua_newuserdata(L, len);
    SIZE_T nr = 0;

    lua_pushboolean(L, ReadProcessMemory(proc, addr, buff, len, &nr));
    lua_pushlightuserdata(L, buff);
    lua_pushinteger(L, nr);

    return 3;
}

static int wapi_WriteProcessMemory(lua_State* L) {
    HANDLE proc = (HANDLE)luaL_optinteger(L, 1, 0);
    LPVOID addr = (LPVOID)luaL_optinteger(L, 2, 0);
    void* buff = lua_touserdata(L, 3);
    SIZE_T len = (SIZE_T)luaL_optinteger(L, 4, 1);
    SIZE_T nr = 0;

    lua_pushboolean(L, WriteProcessMemory(proc, addr, buff, len, &nr));
    lua_pushinteger(L, nr);

    return 2;
}

static const luaL_Reg wapilib[] = {
    { "FindWindow", wapi_FindWindow },
    { "GetWindowThreadProcessId", wapi_GetWindowThreadProcessId },
    { "OpenProcess", wapi_OpenProcess },
    { "ReadProcessMemory", wapi_ReadProcessMemory },
    { "WriteProcessMemory", wapi_WriteProcessMemory },
    { NULL, NULL }
};

LUAMOD_API int luaopen_wapi(lua_State* L) {
    luaL_newlib(L, wapilib);

    return 1;
}