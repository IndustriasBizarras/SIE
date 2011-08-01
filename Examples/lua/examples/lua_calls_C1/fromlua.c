#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <stdio.h>

static int myCfunc ( lua_State *L) {
  printf ("lua SIE's Test\n");
  return 0; }

int luaopen_fromlua ( lua_State *L) {
  static const luaL_reg Map [] = {
    {"dothis", myCfunc},
    {NULL,NULL} } ;
  luaL_register(L, "cstuff", Map);
  return 1; }
