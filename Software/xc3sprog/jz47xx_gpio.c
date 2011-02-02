/*
 * JZ47xx GPIO lines
 *
 * Written 2010 by Andres Calderon andres.calderon@emqbit.com
 */

#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "jz47xx_gpio.h"

#define JZ_GPIO_BASE 0x10010000

PJZ_PIO* pio;

void
jz_gpio_as_output (int port, unsigned int o)
{
  pio[port]->PXFUNC = (1 << (o));
  pio[port]->PXSELC = (1 << (o));
  pio[port]->PXDIRS = (1 << (o));
}

void
jz_gpio_as_input (int port, unsigned int o)
{
  pio[port]->PXFUNC = (1 << (o));
  pio[port]->PXSELC = (1 << (o));
  pio[port]->PXDIRC = (1 << (o));
}

void
jz_gpio_set_pin (int port, unsigned int o)
{
  pio[port]->PXDATS = (1 << (o));
}

void
jz_gpio_clear_pin (int port, unsigned int o)
{
  pio[port]->PXDATC = (1 << (o));
}

void
jz_gpio_out (int port, unsigned int o, unsigned int val)
{
  if (val == 0)
    pio[port]->PXDATC = (1 << (o));
  else
    pio[port]->PXDATS = (1 << (o));
}

unsigned int
jz_gpio_get_pin (int port, unsigned int o)
{
  return (pio[port]->PXPIN & (1 << o)) ? 1 : 0;
}

JZ_PIO *
jz_gpio_map ()
{
  int fd;
  int port;

  JZ_PIO *pio_base;

  pio = (PJZ_PIO*)malloc(sizeof(PJZ_PIO)*4);

  if ((fd = open ("/dev/mem", O_RDWR | O_SYNC)) == -1)
    {
      fprintf (stderr, "Cannot open /dev/mem.\n");
      return 0;
    }

  pio_base = (JZ_PIO *) mmap (0, getpagesize (), PROT_READ | PROT_WRITE, MAP_SHARED, fd, JZ_GPIO_BASE);

  if (pio_base == (JZ_PIO *) - 1)
    {
      fprintf (stderr, "Cannot mmap.\n");
      return 0;
    }
    
  for(port=0; port<4; port++)
    pio[port] = (JZ_PIO *) ((unsigned int) pio_base + port * 0x100);

  return pio_base;
}
