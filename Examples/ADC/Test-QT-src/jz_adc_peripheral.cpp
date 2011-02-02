/* ADC Peripheral.c

Copyright (C) 2010             Carlos Camargo  cicamargoba@unal.edu.co
							   Andres Calderon andres.calderon@emqbit.com

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#include <stdio.h>
#include <unistd.h>

#include "jz_adc_peripheral.h"

JZ_REG *
jz_adc_init()
{
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

	return virt_addr;
}
