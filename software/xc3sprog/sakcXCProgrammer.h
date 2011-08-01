/* at91 XC Programer

Copyright (C) 2006 Carlos Camargo, Andres Calderon

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



#ifndef SAKC_XCP_H
#define SAKC_XCP_H

#include "iobase.h"
#include <unistd.h>


extern "C" 
{
  #include "jz47xx_gpio.h"
}

class sakcXCProgrammer: public IOBase
{
 public:
  sakcXCProgrammer();
  virtual ~sakcXCProgrammer();
  virtual bool txrx(bool tms, bool tdi);
  virtual void tx(bool tms, bool tdi);
  
  bool checkError(){return error;}
  
  bool done(){return true; /*!error && (cpld_base[0]&DONE==DONE);*/}

 protected:
  bool          error;    
  unsigned char data;
};

#define TDI 14 /*C*/
#define TMS 23 /*D*/
#define TDO 24 /*D*/
#define TCK 28 /*D*/

 inline
bool 
sakcXCProgrammer::txrx(bool tms, bool tdi)
{
 tx(tms,tdi);
 return jz_gpio_get_pin (JZ_GPIO_PORT_D, TDO);
}

inline
void 
sakcXCProgrammer::tx(bool tms, bool tdi)
{
  jz_gpio_out (JZ_GPIO_PORT_D, TCK, 0);
  jz_gpio_out (JZ_GPIO_PORT_C, TDI, tdi);
  jz_gpio_out (JZ_GPIO_PORT_D, TMS, tms);
  jz_gpio_out (JZ_GPIO_PORT_D, TCK, 1);
}


#endif // JTAGBUS_H

