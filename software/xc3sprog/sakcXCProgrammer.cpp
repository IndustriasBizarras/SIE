/* JTAG GNU/Linux parport device io

Copyright (C) 2005 Andres Calderon

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
#include <fcntl.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "sakcXCProgrammer.h"

using namespace std;

/*
WE1 TDI PC24
SDA TMS PD23
SCK TDO PD24
    TCK PD28
*/

sakcXCProgrammer::sakcXCProgrammer() : IOBase()
{
  JZ_PIO * pio = jz_gpio_map ();

  jz_gpio_as_input  (JZ_GPIO_PORT_D, TDO);
  jz_gpio_as_output (JZ_GPIO_PORT_D, TCK);
  jz_gpio_as_output (JZ_GPIO_PORT_C, TDI);
  jz_gpio_as_output (JZ_GPIO_PORT_D, TMS);
  
  error = (pio) ? false : true;
}

sakcXCProgrammer::~sakcXCProgrammer()
{
}
