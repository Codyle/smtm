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
#include <smtm/smtm.h>
#include <smtm/lsmtmlib.h>

void luaconst_smtm(lua_State* L)
{
	lua_pushstring(L, SMTM_VERSION);
	lua_setglobal(L, "SMTM_VERSION");
}