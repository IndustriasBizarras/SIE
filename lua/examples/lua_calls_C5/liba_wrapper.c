#include "liba.h"  
  
#include "lua.h"  
#include "lualib.h"  
#include "lauxlib.h"  
  
  
//glue the luaVm and the actually libary  
  
static int lib_a_f_1_wrapper(lua_State * luaVM)  
{  
    // no parameters , just call  
    lib_a_f_1();  
    return 0;  
}  
  
static int lib_a_f_2_wrapper(lua_State * L)  
{  
    // no parameters , just call  
    int n = lua_gettop(L);  
    //error checking & return back to lua scripter  
    int a = lua_tonumber(L,1);  
    int b = lua_tonumber(L,2);  
  
    int r = lib_a_f_2(a ,b );  
  
    lua_pushnumber(L,r);  
    return 1;  
}  
  
  
static int lib_a_f_3_wrapper(lua_State * L)  
{  
    // no parameters , just call  
    int n = lua_gettop(L);  
  
    //error checking & return back to lua scripter  
    const char *s = lua_tostring(L,1);  
  
    int r = lib_a_f_3(s);  
  
    lua_pushnumber(L,r);  
  
    return 1;  
}  
  
const char *metaname = "mine.Point"; // associated with userdata of type Point*  
  
static int lib_a_f_4_wrapper(lua_State *L) {  
    Point *t = luaL_checkudata(L, 1, metaname);  // check argument type  
    lua_pushnumber(L, (lua_Number)lib_a_f_4(t));  
    return 1;  
}  
  
static int point_new_wrapper(lua_State *L) { // get Lua to allocate an initialize a Point*  
    int a = luaL_checkint(L, 1);  
    int b = luaL_checkint(L, 2);  
    //create user data and associate metable with it  
    Point *t = lua_newuserdata(L, sizeof(*t));  
    luaL_getmetatable(L, metaname);  
    lua_setmetatable(L, -2);  
    t->a = a;  
    t->b = b;  
    return 1;  
}  
  
static int point_geta_wrapper(lua_State *L)  
{  
    Point *t = luaL_checkudata(L, 1, metaname);   
    lua_pushnumber(L,t->a);  
  
    return 1;  
}  
  
static int point_getb_wrapper(lua_State *L)  
{  
    Point *t = luaL_checkudata(L, 1, metaname);   
    lua_pushnumber(L,t->b);  
  
    return 1;  
}  
  
static int lib_a_f_5_wrapper(lua_State *L)   
{  
    // Point *t = luaL_checkudata(L, 1, metaname);  // check argument type  
    // lua_pushnumber(L, (lua_Number)lib_a_f_4(t));  
  
    Point t ;  
    lib_a_f_5(&t);  
    Point *r = lua_newuserdata(L,sizeof(*r));  
    luaL_getmetatable(L, metaname);  
    //It will Pops a table from the stack and   
    //sets it as the new metatable for the value at the given acceptable index.   
    //so , after this function , it is the userdata at the top of the stack.   
    lua_setmetatable(L, -2);  
    r->a = t.a;  
    r->b = t.b;  
    return 1;  
}  
  
  
static const struct luaL_reg functions[] = {  
    {"lib_a_f_1", lib_a_f_1_wrapper},  
    {"lib_a_f_2", lib_a_f_2_wrapper},  
    {"lib_a_f_3", lib_a_f_3_wrapper},  
    {"lib_a_f_4", lib_a_f_4_wrapper},  
    {"lib_a_f_5", lib_a_f_5_wrapper},  
    {"point_new", point_new_wrapper},  
    {"point_geta", point_geta_wrapper},  
    {"point_getb", point_getb_wrapper},  
    { NULL, NULL}  
};  
  
//This is the init function that will be called when you require 'mylib'  
  
int luaopen_wrap(lua_State *L) {  
  
  
    luaL_newmetatable(L, metaname);  
    //pop 1 elements from the statck .. why?? to pop the newmetatable that is useless.  
    //  
    //lua_pop(L, 1);  
    //replace luaL_openlib  
    {
        lua_pop(L, 1);
        luaL_newmetatable(L,metaname);
        return 1;
    }
    luaL_register(L, "wrap", functions);  
    return 1;  
}  
