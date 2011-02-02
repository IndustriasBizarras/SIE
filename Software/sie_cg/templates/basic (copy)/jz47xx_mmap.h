/*
 * JZ47xx GPIO lines
 *
 * Written 2010 by Andres Calderon andres.calderon@emqbit.com
 */

#ifndef __jz47xx_mmap_h__
#define __jz47xx_mmap_h__

#include <sys/mman.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "jz47xx_gpio.h"


#define CS2_PORT                 JZ_GPIO_PORT_B
#define CS2_PIN                  26

JZ_REG *virt_addr;

unsigned int * jz_mmap (off_t address);

void jz_cs2_init();

#endif
