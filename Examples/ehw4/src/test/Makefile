#OBJS := start.o main.o jz_serial.o
	
CROSS := mipsel-openwrt-linux-
INCLUDE = -I. -lm
CCFLAGS = ${INCLUDE} ${DEBUG} ${WARNINGS} 
#CFLAGS := -O2 -G 0 -mno-abicalls -fno-pic -mips32 -Iinclude
AFLAGS = -D__ASSEMBLY__ $(CFLAGS)
LDFLAGS := -T ld.script -nostdlib -EL
COMMON_SOURCES =  jz47xx_gpio.c jz47xx_mmap.c 
COMMON_OBJECTS = $(COMMON_SOURCES:.c=.o)
H_SOURCES = jz47xx_gpio.h jz47xx_mmap.h

NANO_IP = 192.168.254.101

all: EvalfitTest

EvalfitTest: EvalfitTest.c evalfit.h $(COMMON_OBJECTS)
	$(CROSS)gcc $(COMMON_OBJECTS) EvalfitTest.c -o EvalfitTest ${CCFLAGS}
	
.c.o:
	$(CROSS)gcc $(CCFLAGS) -c $< -o $@
.S.o:
	$(CROSS)gcc $(AFLAGS) -c $< -o $@
	
indent:
	indent -bad -bap -nbc -bl -nce -i2 --no-tabs --line-length120 $(COMMON_SOURCES) $(H_SOURCES)

clean:
	rm -f *.o EvalfitTest ${OBJECTS} ${EXEC} *~

upload: EvalfitTest
	scp EvalfitTest root@$(NANO_IP):ehw
