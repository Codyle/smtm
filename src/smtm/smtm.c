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
#include <smtm/smtm.h>
#include <smtm/lsmtmlib.h>
#include <smtm/lwapilib.h>

int smtm_run_script(const char* filename)
{
	lua_State* L;
	int result;
	L = luaL_newstate();
	luaL_openlibs(L);
	luaL_requiref(L, "smtm", luaopen_smtm, 1);
	luaL_requiref(L, "wapi", luaopen_wapi, 1);
	lua_pop(L, 1);
	luaL_loadfile(L, filename);
	result = lua_pcall(L, 0, LUA_MULTRET, 0);
	if (result != LUA_OK) {
		fprintf(stderr, "lua: %s\n", lua_tostring(L, -1));
		lua_pop(L, 1);
	}
	lua_close(L);
	return result;
}
