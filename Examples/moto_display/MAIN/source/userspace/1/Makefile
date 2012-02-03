DESIGN = user_space
CC  = mipsel-openwrt-linux-gcc

all: $(DESIGN)

DEBUG = -O3 -g0

COMMON_SOURCES =  jz47xx_gpio.c jz47xx_mmap.c 

H_SOURCES = jz47xx_gpio.h jz47xx_mmap.h

INCLUDE = -I.

WARNINGS= -Wcast-align -Wpacked -Wpadded -Wall

CCFLAGS = ${INCLUDE} ${DEBUG} ${WARNINGS} 

LDFLAGS =

COMMON_OBJECTS = $(COMMON_SOURCES:.c=.o)

NANO_IP = 192.168.200.1

jz_init_sram: $(COMMON_OBJECTS)
	$(CC)  $(LDFLAGS) $(COMMON_OBJECTS) jz_init_sram.c -o jz_init_sram

$(DESIGN): $(COMMON_OBJECTS)
	$(CC)  $(LDFLAGS) $(COMMON_OBJECTS) $(DESIGN).c -o $(DESIGN)



.c.o:
	$(CC) -c $(CCFLAGS) $< -o $@

upload: $(DESIGN) 
	scp $(DESIGN) root@$(NANO_IP):~/pruebas

clean: 
	rm -f *.o  $(DESIGN) ${EXEC} *~

indent:
	indent -bad -bap -nbc -bl -nce -i2 --no-tabs --line-length120 $(COMMON_SOURCES) $(H_SOURCES)
