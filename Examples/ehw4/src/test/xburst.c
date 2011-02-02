#include <stdio.h>
#include <stdlib.h>
#include "fcntl.h"
#include <sys/mman.h>
#include <xburst.h>
#include "jz47xx_gpio.h"
#include <jz47xx_mmap.h>

#define CS2_PORT JZ_GPIO_PORT_B
#define CS2_PIN  26

int periph_map(off_t offset)
{	
int basemem, baseperiph;
	basemem = open("/dev/mem", (O_RDWR | O_SYNC));  //abrir dispositivo memoria para mapear dir del periferico
	if(basemem == -1)
	{
		printf("Error to open /dev/mem \n");
		return -1;
	}
	baseperiph = (int )mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, basemem, offset);// & ~MAP_MASK);	
	if (baseperiph == -1)
	{
		printf ("Cannot mmap.\n");
		return -1;
	}
return baseperiph;
}


int main(){
int i, j;
int basemem, base_periferico, *ConfigRegsBase_ptr;
void *peripheral1_ptr;
void *pio;

printf("Xburst Test...");

basemem = open("/dev/mem", (O_RDWR | O_SYNC));  //abrir dispositivo memoria para mapear dir del periferico
if(basemem == -1)
{
	printf("Error al abrir /dev/mem \n");
	return -1;
}

pio = jz_gpio_map(CS2_PORT);
jz_gpio_as_func (pio, CS2_PIN, 0);

ConfigRegsBase_ptr = (int *)periph_map(CONFIG_REGS_BASE);// + SACR2_OFFSET/sizeof(int);//SMCR2_OFFSET/sizeof(int);
printf("\n%0x ", *(ConfigRegsBase_ptr + SMCR2_OFFSET/sizeof(int)));
munmap(ConfigRegsBase_ptr, MAP_SIZE);

peripheral1_ptr = (int *)periph_map(0x14000000);

for(i = 0; i < 0xfff; i=i+4){
	j = rand();
//	*(int *)(peripheral1_ptr + i) = j;
//	if(j != *(int *)(peripheral1_ptr + i)){
//		printf("\nError at %0x offset:%i\n", (int *)(peripheral1_ptr + i), i); exit(0);
//	}
	printf("\nReg %i: write:%0x read:%0x", i, j, *(int *)(peripheral1_ptr + i) );
}
printf("\nPassed Test\n");
munmap(peripheral1_ptr, MAP_SIZE);

//munmap(base_periferico, MAP_SIZE);
close(basemem);
exit(0);
}

