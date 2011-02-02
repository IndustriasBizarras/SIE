/*
  JZ47xx test gpio 

  Copyright (C) 2010      Andres Calderon andres.calderon@emqbit.com
                          Carlos Camargo  cicamargoba@unal.edu.co
                                 
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

#include "jz47xx_gpio.h"

//#define TEST_PORT JZ_GPIO_PORT_C
//#define TEST_PIN  17 

int
main (int argc,char *argv[])

{
  int TEST_PORT, TEST_PIN;

  if(argc != 3){
    fprintf(stderr,"\nUsage: %s TEST_PIN_PORT(A=0, B=1, C=2, D=3) TEST_PIN \n",argv[0]);
  }

  TEST_PORT = JZ_GPIO_PORT_C;
  TEST_PIN  = 17;
  JZ_PIO *pio = jz_gpio_map (TEST_PORT);

  if (!pio)
    return -1;

  jz_gpio_as_output (pio, TEST_PIN);

  int tg = 1;

  while (1)
    {
      jz_gpio_out (pio, TEST_PIN, tg);
      printf ("[%d]", jz_gpio_get_pin (pio, TEST_PIN));
      fflush (stdout);
      usleep (500 * 1000);
      tg = !tg;
    }
  return 0;
}
