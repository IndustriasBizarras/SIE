/*
 * SIE FPGA init
 * 
 */
 
#include "jz_fpga_init.h"

JZ_REG *
jz_cs2_init()
{
	JZ_PIO *pio;
	JZ_REG *virt_addr;

	pio = jz_gpio_map (CS2_PORT);
	jz_gpio_as_func (pio, CS2_PIN, 0);

	virt_addr = (JZ_REG *) (jz_mmap(0x13010000) + 0x18);

	if (*virt_addr != 0x0FFF7700)
	{
		*virt_addr = 0x0FFF7700;
		printf ("ADC: Configuring CS2 8 bits and 0 WS.\n");
	}
	else
		printf ("ADC: CS2, already configured.\n");

	virt_addr = (JZ_REG *) jz_mmap (0x14000000);
	return virt_addr;
}
