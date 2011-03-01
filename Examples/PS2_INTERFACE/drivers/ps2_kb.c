
#include <linux/types.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <asm/mach-jz4740/gpio.h>

#define FPGA_IRQ_PIN          JZ_GPIO_PORTC(15)
#define FPGA_CS               JZ_GPIO_PORTB(26)
#define FPGA_BASE_BEGIN       0x15000000
#define FPGA_BASE_END         0x17FFFFFF

static unsigned int key_p;
static unsigned int key_e;

/*
 * Scancode to keycode tables. These are just the default setting, and
 * are loadable via a userland utility.
 */

#define ATKBD_KEYMAP_SIZE        512

static const unsigned short atkbd_set2_keycode[ATKBD_KEYMAP_SIZE] = {

#ifdef CONFIG_KEYBOARD_ATKBD_HP_KEYCODES
//stream mode
	iowrite32(0x000000EA,ioaddress);
	mb();
/* XXX: need a more general approach */

#include "hpps2atkbd.h"        /* include the keyboard scancodes */

#else
          0, 67, 65, 63, 61, 59, 60, 88,  0, 68, 66, 64, 62, 15, 41,117,
          0, 56, 42, 93, 29, 16,  2,  0,  0,  0, 44, 31, 30, 17,  3,  0,
          0, 46, 45, 32, 18,  5,  4, 95,  0, 57, 47, 33, 20, 19,  6,183,
          0, 49, 48, 35, 34, 21,  7,184,  0,  0, 50, 36, 22,  8,  9,185,
          0, 51, 37, 23, 24, 11, 10,  0,  0, 52, 53, 38, 39, 25, 12,  0,
          0, 89, 40,  0, 26, 13,  0,  0, 58, 54, 28, 27,  0, 43,  0, 85,
          0, 86, 91, 90, 92,  0, 14, 94,  0, 79,124, 75, 71,121,  0,  0,
         82, 83, 80, 76, 77, 72,  1, 69, 87, 78, 81, 74, 55, 73, 70, 99,

          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        217,100,255,  0, 97,165,  0,  0,156,  0,  0,  0,  0,  0,  0,125,
        173,114,  0,113,  0,  0,  0,126,128,  0,  0,140,  0,  0,  0,127,
        159,  0,115,  0,164,  0,  0,116,158,  0,172,166,  0,  0,  0,142,
        157,  0,  0,  0,  0,  0,  0,  0,155,  0, 98,  0,  0,163,  0,  0,
        226,  0,  0,  0,  0,  0,  0,  0,  0,255, 96,  0,  0,  0,143,  0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,107,  0,105,102,  0,  0,112,
        110,111,108,112,106,103,  0,119,  0,118,109,  0, 99,104,119,  0,

          0,  0,  0, 65, 99,
#endif
};

static struct input_dev *ps2kbd_dev;
static void __iomem *ioaddress;

static irqreturn_t ps2_keyboard_interrupt(int irq, void *id)
{
        unsigned char scancode, keycode;
        
        scancode = (unsigned char)(ioread32(ioaddress)& 0XFF);
        rmb();
        
        //printk(KERN_INFO "scancode %x\n", scancode);
        
        if      (scancode == 0xAA)printk(KERN_INFO "PS/2 keyboard. ok\n");
	else if (scancode == 0xFC)printk(KERN_INFO "PS/2 keyboard. error\n");
        else if (scancode == 0xF0)key_p=0;
        else if (scancode == 0xE0)key_e=1;
        else if (scancode <= 0x7E){                /* scancodes < 0xf2 are keys */

                keycode = atkbd_set2_keycode[scancode+0x80*key_e];

                input_report_key(ps2kbd_dev, keycode, key_p);
                input_sync(ps2kbd_dev);
                key_p=1;
                key_e=0;
        } else                                /* scancodes >= 0xf2 are mouse data, most likely */
                printk(KERN_INFO "ps2kbd: unhandled scancode %x\n", scancode);
	
        return IRQ_HANDLED;
}
        
static int __init ps2_keyboard_init(void)
{
        
        int i, error, res, irq;
        
        key_p=1;
        key_e=0;
        
        ps2kbd_dev = input_allocate_device();
        if (!ps2kbd_dev)
                return -ENOMEM;
        
        ps2kbd_dev->name = "PS2 Keyboard";
        ps2kbd_dev->phys = "ps2kbd/input0";
        ps2kbd_dev->id.bustype = BUS_HOST;
        ps2kbd_dev->id.vendor = 0x0001;
        ps2kbd_dev->id.product = 0x0001;
        ps2kbd_dev->id.version = 0x0100;

        ps2kbd_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
        ps2kbd_dev->keycode = atkbd_set2_keycode;
        ps2kbd_dev->keycodesize = sizeof(unsigned short);
        ps2kbd_dev->keycodemax = ARRAY_SIZE(atkbd_set2_keycode);

        for (i = 0; i < ATKBD_KEYMAP_SIZE; i++) {
                set_bit(atkbd_set2_keycode[i], ps2kbd_dev->keybit);
        }
        
        /* error check */
        error = input_register_device(ps2kbd_dev);
        if (error) {
                input_free_device(ps2kbd_dev);
                return error;
        }
        
        /* Set up the FGPA irq line */ 
        irq = gpio_to_irq(FPGA_IRQ_PIN);
        res = request_irq(irq, ps2_keyboard_interrupt, IRQF_DISABLED | IRQF_TRIGGER_RISING, "FPGA - IRQ", NULL); // IRQF_TRIGGER_FALLING
        
        /* Set GPIOB26 as part of External Memory Controller*/
        jz_gpio_set_function (FPGA_CS, JZ_GPIO_FUNC_NONE);
        /* Use ioremap to get a handle on our region */
        ioaddress = __ioremap(FPGA_BASE_BEGIN, FPGA_BASE_END - FPGA_BASE_BEGIN, _CACHE_UNCACHED);

        return 0;
}

static void __exit ps2_keyboard_exit(void)
{       
        free_irq(FPGA_IRQ_PIN, NULL);
        __iounmap(ioaddress);
        input_unregister_device(ps2kbd_dev);
}

module_init(ps2_keyboard_init);
module_exit(ps2_keyboard_exit);

MODULE_AUTHOR("Ari Bejarano <aabejaranoh@unal.edu.co>");
MODULE_DESCRIPTION("PS/2 Keyboard Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:ps2-keyboard");
