/*
 * SIE FPGA init
 * 
 */
#include "jz47xx_gpio.h"
#include "jz47xx_mmap.h"

#define CS2_PORT                 JZ_GPIO_PORT_B
#define CS2_PIN                  26

JZ_REG * jz_cs2_init();

