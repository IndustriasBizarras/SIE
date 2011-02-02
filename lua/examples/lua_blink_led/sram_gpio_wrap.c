#include <jz47xx_gpio.h>
#include <jz47xx_mmap.h>
  
#include "lua.h"  
#include "lualib.h"  
#include "lauxlib.h"    
  
const char *metaname = "mine.JZ_PIO"; // associated with userdata of type Point*  
  
static int jz_gpio_as_output_wrap(lua_State *L) {  
    JZ_PIO *pio = (JZ_PIO *)lua_touserdata(L,1);
    luaL_checkudata(L, 1, metaname);  // check argument type  
    int pin = luaL_checkint(L, 2);  
    lua_pushnumber(L, (lua_Number)jz_gpio_as_output(pio, pin)); 
    return 1;  
}

static int jz_gpio_set_pin_wrap(lua_State *L) {  
    JZ_PIO *pio = luaL_checkudata(L, 1, metaname);  // check argument type  
    int pin = luaL_checkint(L, 2);  
    lua_pushnumber(L, (lua_Number)jz_gpio_set_pin(pio, pin));  
    return 1;  
}

static int jz_gpio_clear_pin_wrap(lua_State *L) {  
    JZ_PIO *pio = luaL_checkudata(L, 1, metaname);  // check argument type  
    int pin = luaL_checkint(L, 2);  
    lua_pushnumber(L, (lua_Number)jz_gpio_clear_pin(pio, pin));  
    return 1;  
}

  

static int open_port_wrapper(lua_State *L) { // get Lua to allocate an initialize a Point*  
    int port = luaL_checkint(L, 1);
    //create user data and associate metable with it  
    JZ_PIO *pio = jz_gpio_map (port);
    lua_pushlightuserdata(L,pio);
    luaL_getmetatable(L, metaname);  
    lua_setmetatable(L, -2);  
    return 1;  
}  

static const struct luaL_reg functions[] = {  
    {"gpio_as_output", jz_gpio_as_output_wrap},  
    {"set_pin", jz_gpio_set_pin_wrap},  
    {"clear_pin", jz_gpio_clear_pin_wrap},  
    {"open_port", open_port_wrapper},  
    { NULL, NULL}  
};  
  
//This is the init function that will be called when you require 'gpio'  
  
int luaopen_gpio(lua_State *L) {  
    luaL_newmetatable(L, metaname);  
    //pop 1 elements from the statck .. why?? to pop the newmetatable that is useless.  
    //  
    //lua_pop(L, 1);  
    //replace luaL_openlib  
    luaL_register(L, "gpio", functions);  
    return 1;  
}  
