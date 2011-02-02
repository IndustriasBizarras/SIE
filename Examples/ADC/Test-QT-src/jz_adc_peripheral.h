/* ADC Peripheral.h

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

#ifndef __adc_peripheral_h__
#define __adc_peripheral_h__

#include "jz47xx_mmap.h"
#include "jz47xx_gpio.h"

#define ADC_CMD_NONE             0x00 /* Nothing to do                        */
#define ADC_CMD_SET_SPI_CLKDIV   0x00 /* Set clock divider for ADC sclk       */
#define ADC_CMD_SET_BUFFER_SIZE  0x00 /* Set clock divider for ADC sclk       */

#define ADC_CMD_SET_CHANNEL0     0x30 /* Set channel 0                        */
#define ADC_CMD_READ_CHANNEL0    0x20 /* Read channel 0                       */

#define ADC_CMD_SET_CHANNEL1     0x31 /* Set channel 1                        */
#define ADC_CMD_READ_CHANNEL1    0x21 /* Read channel 1                       */

#define ADC_CMD_SET_CHANNEL2     0x32 /* Set channel 2                        */
#define ADC_CMD_READ_CHANNEL2    0x22 /* Read channel 2                       */

#define ADC_CMD_SET_CHANNEL3     0x33 /* Set channel 3                        */
#define ADC_CMD_READ_CHANNEL3    0x23 /* Read channel 3                       */

#define ADC_CMD_SET_CHANNEL4     0x34 /* Set channel 4                        */
#define ADC_CMD_READ_CHANNEL4    0x24 /* Read channel 4                       */

#define ADC_CMD_SET_CHANNEL5     0x35 /* Set channel 5                        */
#define ADC_CMD_READ_CHANNEL5    0x25 /* Read channel 5                       */

#define ADC_CMD_SET_CHANNEL6     0x36 /* Set channel 6                        */
#define ADC_CMD_READ_CHANNEL6    0x26 /* Read channel 6                       */

#define ADC_CMD_SET_CHANNEL7     0x37 /* Set channel 7                        */
#define ADC_CMD_READ_CHANNEL7    0x27 /* Read channel 8                       */

#define ADC_CMD_SET_POWER_DOWN   0X38 /* Set ADC power down mode  (1uA)       */

#define ADC_CMD_SET_FAST_CONV    0X39 /* Initialize ADC Fast Convertion(<10us)*/

#define ADC_CMD_SET_LOW_CONV     0X3A /* Initialize ADC Slow Convertion(<40us)*/

#define ADC_CMD_SET_AUTOSELFT_1  0x3B /* Set Autoselft ADC {(Vref+)-(Vref-)}/2*/
#define ADC_CMD_READ_AUTOSELFT_1 0x2B /* Read Autoselft ADC 1 (0x0200)        */

#define ADC_CMD_SET_AUTOSELFT_2  0x3C /* Set Autoselft ADC (Vref-)            */
#define ADC_CMD_READ_AUTOSELFT_2 0x2C /* Read Autoselft ADC 2 (0x0000)        */

#define ADC_CMD_SET_AUTOSELFT_3  0x3D /* Set Autoselft ADC (Vref+)            */
#define ADC_CMD_READ_AUTOSELFT_3 0x2D /* Read Autoselft ADC 3 (0x03FF)        */

#define ADC_SPI_CLKDIV_MIN       0x08 /* 50/(2*9) -> 2.78MHz (MAX=2.8MHz)     */
#define ADC_SPI_CLKDIV_MAX       0xFF /* 50/(2*256) -> 97.65KHz               */

#define ADC_MAX_BUFFER           0x3FE/* 1022 reads/commands                  */

#define CS2_PORT                 JZ_GPIO_PORT_B
#define CS2_PIN                  26

typedef unsigned char uchar;

JZ_REG *jz_adc_init();

#endif
