/*
 * Copyright (c) 2009 Qi Hardware Inc.,
 * Author: Xiangfu Liu <xiangfu@qi-hardware.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __ASM_JZ4725_SAKC_H__
#define __ASM_JZ4725_SAKC_H__

#include <linux/gpio.h>
/*
 * Frequencies of on-board oscillators
 */
#define JZ_EXTAL		12000000  /* Main extal freq: 12 MHz */
#define JZ_EXTAL_RTC		32768     /* RTC extal freq: 32.768 KHz */

/*
 * GPIO
 */

#define GPIO_SD_CD_N            JZ_GPIO_PORTC(27)

#endif /* __ASM_JZ4725_SAKC_H__ */
