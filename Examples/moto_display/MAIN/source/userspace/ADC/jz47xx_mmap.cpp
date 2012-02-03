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
