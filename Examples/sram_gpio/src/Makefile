CC  = mipsel-openwrt-linux-gcc

all: jz_init_sram jz_test_gpio enable_rx enable_irq

DEBUG = -O3 -g0

COMMON_SOURCES =  jz47xx_gpio.c jz47xx_mmap.c 

H_SOURCES = jz47xx_gpio.h jz47xx_mmap.h

INCLUDE = -I.

WARNINGS= -Wcast-align -Wpacked -Wpadded -Wall

CCFLAGS = ${INCLUDE} ${DEBUG} ${WARNINGS} 

LDFLAGS =

COMMON_OBJECTS = $(COMMON_SOURCES:.c=.o)

NANO_IP = 192.168.254.101

jz_init_sram: $(COMMON_OBJECTS) jz_init_sram.o
	$(CC)  $(LDFLAGS) $(COMMON_OBJECTS) jz_init_sram.o -o jz_init_sram

jz_test_gpio: $(COMMON_OBJECTS) jz_test_gpio.o
	$(CC)  $(LDFLAGS) $(COMMON_OBJECTS) jz_test_gpio.o -o jz_test_gpio

enable_rx: $(COMMON_OBJECTS) enable_rx.o
	$(CC)  $(LDFLAGS) $(COMMON_OBJECTS) enable_rx.o  -o enable_rx

enable_irq: $(COMMON_OBJECTS) enable_irq.o
	$(CC)  $(LDFLAGS) $(COMMON_OBJECTS) enable_irq.o -o enable_irq

.c.o:
	$(CC) -c $(CCFLAGS) $< -o $@

upload: jz_init_sram jz_test_gpio 
	scp jz_test_gpio jz_init_sram root@$(NANO_IP):

clean: 
	rm -f *.o jz_init_sram jz_test_gpio enable_rx  ${EXEC} *~ enable_irq

indent:
	indent -bad -bap -nbc -bl -nce -i2 --no-tabs --line-length120 $(COMMON_SOURCES) $(H_SOURCES)
