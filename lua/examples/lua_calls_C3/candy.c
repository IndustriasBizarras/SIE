
/* This is the third (of three) examples of calling from
a Lua script to a C library.  In this example, we have
registered multiple C functions with the Lua, and we have
also passed in a table which is intrinically much harder
to handle as it doesn't map directly to a C type. */

#include "lua.h"
#include "lauxlib.h"
#include <stdio.h>

/* The peardrop function is called with a single
numeric  parameter, and it returns a number */

static int peardrop ( lua_State *L) {
        printf ("lua SIE's test\n");
        double trouble = lua_tonumber(L, 1);
        lua_pushnumber(L, 16.0 - trouble);
        return 1;
        }

/* The humbug function is called with a TABLE as
its parameter (or it should be!).  It extracts the
element with the key "hq", and returns 123 more
than that number (the sum added is just done to
demonstrate the C doing something! */

static int humbug ( lua_State *L) {
        printf ("Enter humbug function\n");

        /* Is it a table? */
        if (lua_istable(L,-1)) {
                printf("Table passed to humbug\n");

                /* Looking up based on the key */
                /* Add key we're interested in to the stack*/
                lua_pushstring(L,"hq");
                /* Have Lua functions look up the keyed value */
                lua_gettable(L, -2 );
                /* Extract the result which is on the stack */
                double workon = lua_tonumber(L,-1);
                /* Tidy up the stack - get rid of the extra we added*/
                lua_pop(L,1);

                /* We can now use the result */
                lua_pushnumber(L, workon + 123.0 );
        } else {
                printf("Not a Table passed to humbug\n");
                lua_pushnumber(L, 12.0 );
        }
        return 1;
        }

/* This registers "dothis" and "dothat" with Lua, so that when
they're called they run the humbug and peardrop functions respectively */

int luaopen_candy ( lua_State *L) {
        static const luaL_reg Map [] = {
                {"dothis", humbug},
                {"dothat", peardrop},
                {NULL,NULL}
                } ;
        /* dothis and dothat are put in the extratasks table */
        luaL_register(L, "extratasks", Map);
        return 1;
        }
         
