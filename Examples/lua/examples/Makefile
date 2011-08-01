DIRS   = lua_blink_led  lua_calls_C1  lua_calls_C2  lua_calls_C3   lua_calls_C5
all:
	for n in $(DIRS); do $(MAKE) -C $$n || exit 1; done

upload:
	for n in $(DIRS); do $(MAKE) -C $$n upload || exit 1; done

clean:
	for n in $(DIRS); do $(MAKE) -C $$n clean || exit 1; done 

