/*
 * linux/arch/mips/jz4740/board-sakc.c
 *
 * SAKC setup routines, based on QI_LB60
 *
 * Copyright (c) 2009 Qi Hardware inc.,
 * Author: Xiangfu Liu <xiangfu@qi-hardware.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 or later
 * as published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>

#include <asm/mach-jz4740/board-sakc.h>
#include <asm/mach-jz4740/platform.h>

#include <linux/input.h>
//#include <linux/gpio_keys.h>
#include <linux/mtd/jz4740_nand.h>
#include <linux/jz4740_fb.h>
//#include <linux/input/matrix_keypad.h>
#include <linux/mtd/jz4740_nand.h>
#include <linux/spi/spi.h>
#include <linux/spi/spi_gpio.h>
//#include <linux/power_supply.h>
//#include <linux/power/jz4740-battery.h>
//#include <linux/power/gpio-charger.h>
#include <linux/mmc/jz4740_mmc.h>


/* NAND */
static struct nand_ecclayout sakc_ecclayout_1gb = {
	.eccbytes = 36,
	.eccpos = {
		6,  7,  8,  9,  10, 11, 12, 13,
		14, 15, 16, 17, 18, 19, 20, 21,
		22, 23, 24, 25, 26, 27, 28, 29,
		30, 31, 32, 33, 34, 35, 36, 37,
		38, 39, 40, 41},
	.oobfree = {
		{.offset = 2,
		 .length = 4},
		{.offset = 42,
		 .length = 22}}
};

static struct mtd_partition sakc_partitions_1gb[] = {
	{ .name = "NAND BOOT partition",
	  .offset = 0 * 0x100000,
	  .size = 4 * 0x100000,
 	},
	{ .name = "NAND KERNEL partition",
	  .offset = 4 * 0x100000,
	  .size = 4 * 0x100000,
 	},
	{ .name = "NAND ROOTFS partition",
	  .offset = 8 * 0x100000,
	  .size = (504 + 512) * 0x100000,
 	},
};

static struct nand_ecclayout sakc_ecclayout_2gb = {
	.eccbytes = 72,
	.eccpos = {
		12, 13, 14, 15, 16, 17, 18, 19,
		20, 21, 22, 23, 24, 25, 26, 27, 
		28, 29, 30, 31, 32, 33, 34, 35,
		36, 37, 38, 39, 40, 41, 42, 43,
		44, 45, 46, 47, 48, 49, 50, 51, 
		52, 53, 54, 55, 56, 57, 58, 59, 
		60, 61, 62, 63, 64, 65, 66, 67, 
		68, 69, 70, 71, 72, 73, 74, 75, 
		76, 77, 78, 79, 80, 81, 82, 83},
	.oobfree = {
 		{.offset = 2,
		 .length = 10},
		{.offset = 84,
		 .length = 44}}
};

static struct mtd_partition sakc_partitions_2gb[] = {
	{ .name = "NAND BOOT partition",
	  .offset = 0 * 0x100000,
	  .size = 4 * 0x100000,
 	},
	{ .name = "NAND KERNEL partition",
	  .offset = 4 * 0x100000,
	  .size = 4 * 0x100000,
 	},
	{ .name = "NAND ROOTFS partition",
	  .offset = 8 * 0x100000,
	  .size = (504 + 512 + 1024) * 0x100000,
 	},
};

static void sakc_nand_ident(struct platform_device *pdev,
				struct nand_chip *chip, 
				struct mtd_partition **partitions,
				int *num_partitions)
{
	if (chip->page_shift == 12) {
		chip->ecc.layout = &sakc_ecclayout_2gb;
		*partitions = sakc_partitions_2gb;
		*num_partitions = ARRAY_SIZE(sakc_partitions_2gb);
	} else {
		chip->ecc.layout = &sakc_ecclayout_1gb;
		*partitions = sakc_partitions_1gb;
		*num_partitions = ARRAY_SIZE(sakc_partitions_1gb);
	}
}

static struct jz_nand_platform_data sakc_nand_pdata = {
	.ident_callback = sakc_nand_ident,
	.busy_gpio = 94,
};


/* Display */
static struct fb_videomode sakc_video_modes[] = {
	{
		.name = "320x240",
		.xres = 320,
		.yres = 240,
		.pixclock = 700000,
		.left_margin = 140,
		.right_margin = 273,
		.upper_margin = 20,
		.lower_margin = 2,
		.hsync_len = 1,
		.vsync_len = 1,
		.sync = 0,
		.vmode = FB_VMODE_NONINTERLACED,
	},
};

static struct jz4740_fb_platform_data sakc_fb_pdata = {
	.width		= 60,
	.height		= 45,
	.num_modes	= ARRAY_SIZE(sakc_video_modes),
	.modes		= sakc_video_modes,
	.bpp		= 24,
	.lcd_type	= JZ_LCD_TYPE_8BIT_SERIAL,
};


struct spi_gpio_platform_data spigpio_platform_data = {
	.sck = JZ_GPIO_PORTC(23),
	.mosi = JZ_GPIO_PORTC(22),
	.miso = JZ_GPIO_PORTC(22),
	.num_chipselect = 1,
};

static struct platform_device spigpio_device = {
	.name = "spi_gpio",
	.id   = 1,
	.dev = {
		.platform_data = &spigpio_platform_data,
	},
};

static struct spi_board_info sakc_spi_board_info[] = {
	{
		.modalias = "gpm940b0",
		.controller_data = (void*)JZ_GPIO_PORTC(21),
		.chip_select = 0,
		.bus_num = 1,
		.max_speed_hz = 30 * 1000,
	},
};

/* MMC */

static struct jz4740_mmc_platform_data sakc_mmc_pdata = {
	.gpio_card_detect	= JZ_GPIO_PORTC(27),
	.gpio_read_only		= -1,
	.gpio_power			= -1,
	.power_active_low	= 1,
	.data_1bit			= 1,
};

static struct platform_device *jz_platform_devices[] __initdata = {
	&jz4740_usb_ohci_device,
	&jz4740_usb_gdt_device,
	&jz4740_mmc_device,
	&jz4740_nand_device,
	&spigpio_device,
	&jz4740_framebuffer_device,
	&jz4740_i2s_device,
	&jz4740_codec_device,
	&jz4740_rtc_device,
	&jz4740_adc_device,
};

static void __init board_gpio_setup(void)
{
	/* We only need to enable/disable pullup here for pins used in generic
	 * drivers. Everything else is done by the drivers themselfs. */
	jz_gpio_disable_pullup(GPIO_SD_CD_N);
}

static int __init sakc_init_platform_devices(void)
{
	jz4740_framebuffer_device.dev.platform_data = &sakc_fb_pdata;
	jz4740_nand_device.dev.platform_data = &sakc_nand_pdata;
	jz4740_mmc_device.dev.platform_data = &sakc_mmc_pdata;

	spi_register_board_info(sakc_spi_board_info,
				ARRAY_SIZE(sakc_spi_board_info));

	return platform_add_devices(jz_platform_devices,
					ARRAY_SIZE(jz_platform_devices));

}
extern int jz_gpiolib_init(void);
extern int jz_init_clocks(unsigned long extal);

static __init int board_sakc(char *str)
{
	sakc_mmc_pdata.card_detect_active_low = 1;

	return 1;
}

__setup("sakc", board_sakc);

static int __init sakc_board_setup(void)
{
	printk("Qi Hardware JZ4725 SAKC setup\n");
	if (jz_gpiolib_init())
		panic("Failed to initalize jz gpio\n");
	jz_init_clocks(12000000);

	board_gpio_setup();

	if (sakc_init_platform_devices())
		panic("Failed to initalize platform devices\n");

	return 0;
}

arch_initcall(sakc_board_setup);
