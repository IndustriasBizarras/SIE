CROSS = mipsel-openwrt-linux-gcc
CC = gcc

all: client_jz server_jz client_386 server_386

DEBUG = -O3 -g0

COMMON_SOURCES =  jz47xx_gpio.c jz47xx_mmap.c

H_SOURCES = jz47xx_gpio.h jz47xx_mmap.h

INCLUDE = -I.

WARNINGS= -Wcast-align -Wpacked -Wpadded -Wall

CCFLAGS = ${INCLUDE} ${DEBUG} ${WARNINGS} 

LDFLAGS =

COMMON_OBJECTS_JZ = jz47xx_gpio_jz.o jz47xx_mmap_jz.o
COMMON_OBJECTS_386 = jz47xx_gpio_386.o jz47xx_mmap_386.o

NANO_IP = 192.168.254.101

genetic_jz.o: genetic.c genetic.h $(COMMON_OBJECTS_JZ)
	${CROSS} -lm -I. -c genetic.c $(COMMON_OBJECTS_JZ) -o genetic_jz.o

client_jz: sintesishw_client.c genetic_jz.o sintesishw_client.h $(COMMON_OBJECTS_JZ)
	${CROSS} sintesishw_client.c genetic_jz.o  $(COMMON_OBJECTS_JZ) -o sintesishw_client_jz -lm -I.

server_jz: sintesishw_server.c genetic_jz.o $(COMMON_OBJECTS_JZ)
	${CROSS} sintesishw_server.c genetic_jz.o  $(COMMON_OBJECTS_JZ) -o sintesishw_server_jz -lm -lpthread -I.

jz47xx_mmap_jz.o: jz47xx_mmap.c jz47xx_mmap.h
	${CROSS} -lm -I. -c jz47xx_mmap.c -o jz47xx_mmap_jz.o

jz47xx_gpio_jz.o: jz47xx_gpio.c jz47xx_gpio.h
	${CROSS} -lm -I. -c jz47xx_gpio.c -o jz47xx_gpio_jz.o



genetic_386.o: genetic.c genetic.h $(COMMON_OBJECTS_386)
	${CC} -lm -I. -c genetic.c  $(COMMON_OBJECTS_386) -o genetic_386.o

client_386: sintesishw_client.c genetic_386.o sintesishw_client.h $(COMMON_OBJECTS_386)
	${CC} sintesishw_client.c genetic_386.o $(COMMON_OBJECTS_386) -o sintesishw_client_386 -lm -I.

server_386: sintesishw_server.c genetic_386.o $(COMMON_OBJECTS_386)
	${CC} sintesishw_server.c genetic_386.o $(COMMON_OBJECTS_386) -o sintesishw_server_386 -lm -lpthread -I.

jz47xx_mmap_386.o: jz47xx_mmap.c jz47xx_mmap.h
	${CC} -lm -I. -c jz47xx_mmap.c -o jz47xx_mmap_386.o

jz47xx_gpio_386.o: jz47xx_gpio.c jz47xx_gpio.h
	${CC} -lm -I. -c jz47xx_gpio.c -o jz47xx_gpio_386.o



upload: sintesishw_server_jz
	scp sintesishw_server_jz root@$(NANO_IP):ehw

clean: 
	rm -f *.o sintesishw_client_jz sintesishw_server_jz  sintesishw_client_386 sintesishw_server_386 ${EXEC} *~
