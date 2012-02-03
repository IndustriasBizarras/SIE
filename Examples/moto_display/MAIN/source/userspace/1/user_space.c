#include "jz47xx_gpio.h"
#include "jz47xx_mmap.h"
#include <stdio.h>
 
#define CS2_PORT JZ_GPIO_PORT_B
#define CS2_PIN  26
 
int main (){

  JZ_PIO *pio;
	JZ_REG *virt_addr;

	pio = jz_gpio_map (CS2_PORT);
	jz_gpio_as_func (pio, CS2_PIN, 0);

	virt_addr = (JZ_REG *) (jz_mmap(0x13010000) + 0x18);

	if (*virt_addr != 0x0FFF7700)
	{
		*virt_addr = 0x0FFF7700;
		printf ("ADC: Configuring CS2 8 bits and 0 WS: %08X\n", *virt_addr);
	}
	else
		printf ("ADC: CS2, already configured: %08X\n", *virt_addr);

	virt_addr = (JZ_REG *) jz_mmap (0x14000000);
	char A=0;
	while(1)
	{
	int tmp = virt_addr[0x00];
	if(tmp != A)
	{ 
	printf("Hola: %d\n",virt_addr[0x00]);
	A = virt_addr[0x00];
	}
	}
  return 0;
}
