/*
 * JZ47xx GPIO lines
 *
 * Written 2010 by Andres Calderon andres.calderon@emqbit.com
 */

#ifndef __jz47xx_mmap_h__
#define __jz47xx_mmap_h__

#include <sys/mman.h>

unsigned int * jz_mmap (off_t address);

#endif
