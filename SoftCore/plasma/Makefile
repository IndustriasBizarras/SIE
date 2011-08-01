TARGET = bootldr
DIRS   = tools bootldr logic gpio

all:
	for n in $(DIRS); do $(MAKE) -C $$n || exit 1; done

tool:
	make -C tools 

logic:
	make -C logic 

bootldr: tool
	make -C bootldr

clean:
	for n in $(DIRS); do $(MAKE) -C $$n clean || exit 1; done 
