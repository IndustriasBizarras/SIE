/* SAKC FPGA/SRAM interface test

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
#include <stdlib.h>

#include "jz47xx_gpio.h"
#include "jz47xx_mmap.h"

#define CS2_PORT JZ_GPIO_PORT_B
#define CS2_PIN  26

int
main ()
{
  int i;
  JZ_PIO *pio;
  int *virt_addr;

  pio = jz_gpio_map (CS2_PORT);
  jz_gpio_as_func (pio, CS2_PIN, 0);

  virt_addr = (int *) jz_mmap (0x13010000) + 0x18/sizeof(int);

  if (*virt_addr != 0xFFF7700)
    {                           // 0 WS, 8 bits
      *virt_addr = 0xFFF7700;
      printf ("Configuring CS2 8 bits \n");
    }
  else
    printf ("CS3, already configured\n");

  virt_addr = (int *) jz_fpga_map (0x15000000);

  printf ("Writing Memory..\n");

  srand48(0x3c);

  for (i = 0; i < FPGA_SIZE/4; i++)
      virt_addr[i] = (lrand48() & 0x00ff);

  printf ("Reading Memory..\n");


  srand48(0x3c);

  for (i = 0; i < FPGA_SIZE/4; i++){
    printf("%X\n", virt_addr[i]);
    if (virt_addr[i] != (lrand48() & 0x00ff)){
      printf ("FPGA - Xburst connection test failed on Address:0x%x\n", i);
      return 1; /* Error */
    }
  }
  printf ("%d\n", i);
      printf ("FPGA - Xburst connection test passed\n");

  return 0;
}
