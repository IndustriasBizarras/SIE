/*
 * JZ47xx GPIO lines
 *
 * Written 2010 by Andres Calderon andres.calderon@emqbit.com
 */

#include "jz47xx_mmap.h"

unsigned int *
jz_mmap (off_t address)
{
  int fd;

  unsigned int *pio;

  if ((fd = open ("/dev/mem", O_RDWR | O_SYNC)) == -1)
    {
      fprintf (stderr, "Cannot open /dev/mem.\n");
      return 0;
    }

  pio = (unsigned int *) mmap (0, getpagesize (), PROT_READ | PROT_WRITE, MAP_SHARED, fd, address);

  if (pio == (unsigned int *) -1)
    {
      fprintf (stderr, "Cannot mmap.\n");
      return 0;
    }

  return pio;
}

void
jz_cs2_init()
{
	JZ_PIO *pio;	

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
}

