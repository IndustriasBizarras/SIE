
--[[ This is a short (demonstration) piece of Lua
script which calls in some C functions from a file
called candy.c;   the functions are accessed via a
table called extratasks (that's defines in the
C code) and called via the names dothis and dothat -
again defined in the candy.c file
]]

-- Setting up demo variables that will be passed to C
print("Lua code running ...")
stuff = {hotel = 48, hq = 404, town = 1}

-- Loading and calling the C
require "candy"
summat = extratasks.dothis(stuff)
somemore = extratasks.dothat(summat)

-- Lua code to show you the results
print ("... back into Lua code")
print ("Values in Lua now", summat, somemore)
print ("Table contains ...")
for k,v in pairs(stuff) do
        print (k,v)
        end
