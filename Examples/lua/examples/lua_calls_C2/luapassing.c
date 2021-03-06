#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <stdio.h>


static int myCfunc ( lua_State *L) {
  printf ("lua SIE's test\n");
  double trouble = lua_tonumber(L, 1);
  lua_pushnumber(L, 16.0 - trouble);
  return 1; }


int luaopen_luapassing ( lua_State *L) {
  static const luaL_reg Map [] = {
    {"dothis", myCfunc},
    {NULL,NULL} } ;
  luaL_register(L, "cstuff", Map);
  return 1; }
