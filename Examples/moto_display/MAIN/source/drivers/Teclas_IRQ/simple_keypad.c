/***************************************************************/
/*          Driver para el periferico keypad                   */
/*                                                             */
/*          Universidad Nacional de Colombia                   */
/*                                                             */
/*          Autores: Cesar Augusto Pantoja                     */
/*                   Felipe Andres Navarro                     */
/*                                                             */
/*          Proyecto: Dispositivo de informacion               */
/*                    para vehiculos automotores               */
/*                                                             */
/***************************************************************/

#include <linux/init.h>
#include <linux/slab.h> 
#include <linux/errno.h> 
#include <linux/types.h> 
#include <linux/proc_fs.h>
#include <linux/fcntl.h> 
#include <asm/system.h> 
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/ioport.h>
#include <linux/device.h>
#include <linux/interrupt.h>  
#include <linux/irq.h>        
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/delay.h>
#include <asm/uaccess.h>  
#include <asm/io.h>
#include <linux/gpio.h>
#include <asm/mach-jz4740/gpio.h>
#include <linux/input.h>
#include <linux/clk.h>
#include <linux/mmc/host.h>
#include <linux/io.h>
#include <linux/scatterlist.h>

#define CS2_PIN				JZ_GPIO_PORTB(26)
#define FPGA_IRQ_PIN		        JZ_GPIO_PORTC(15)  //pin del irq
#define FPGA_BASE 			0xB5000000         //direccion virtual base de la FPGA
#define KEYPAD_OFFSET 	        	0x1000             //Direccion del modulo periférico keypad en la FPGA

MODULE_AUTHOR("Cesar Pantoja, Felipe Navarro");
MODULE_DESCRIPTION("Simple Keypad Driver");
MODULE_LICENSE("GPL");

static unsigned int keypad_code[] = {
	KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
	KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P,
	KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_BACKSPACE,
	KEY_ESC, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_EQUAL, KEY_ENTER,
	KEY_TAB, KEY_LEFTBRACE, KEY_RIGHTBRACE, KEY_COMMA, KEY_DOT, KEY_BACKSLASH, KEY_SLASH, KEY_APOSTROPHE, KEY_UP, KEY_SEMICOLON,
	KEY_LEFTSHIFT, KEY_RIGHTALT, KEY_LEFTALT, KEY_SPACE, KEY_RIGHTCTRL, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_MINUS, KEY_RIGHTALT
};

unsigned int irq;
static unsigned int keydecode(unsigned char valor){
	unsigned int salida;
	switch(valor){
		case 1:  salida=KEY_1;    break;
		case 2:  salida=KEY_2;    break;
		case 3:  salida=KEY_3;    break;
		case 4:  salida=KEY_4;    break;
		case 86: salida=KEY_ENTER;break;
		case 75: salida=KEY_5;    break;
		case 202:salida=KEY_UP;   break;
		case 84: salida=KEY_LEFT; break;
		case 182:salida=KEY_DOWN; break;
		case 232:salida=KEY_TAB;  break;  //KEY_RIGHT
		default: salida=0;        break;
		}
return salida;
} 

static struct input_dev *keypad;

//funcion que atiende las interrupciones y define las acciones a tomar
static irqreturn_t irq_handler(int irq, void *dev_id){  
	printk("%d\n",inb(FPGA_BASE+KEYPAD_OFFSET));
		if(inb(FPGA_BASE+KEYPAD_OFFSET)==00)
		{	
			return IRQ_HANDLED;
		}
		else 
		{
			input_report_key(keypad,keydecode(inb(FPGA_BASE+KEYPAD_OFFSET)),1);
	        	input_report_key(keypad,keydecode(inb(FPGA_BASE+KEYPAD_OFFSET)),0);
			input_sync(keypad);
	   		return IRQ_HANDLED;
	   	}
}

static int __init skpad_init(void)
{
	int i, error,res;
	keypad = input_allocate_device();
	jz_gpio_set_function(CS2_PIN, JZ_GPIO_FUNC1);
	if (!keypad)
		return -ENOMEM;

	keypad->name = "SIMPLE Keypad"; //asignacion de datos del teclado
	keypad->phys = "keypad/input0"; //direccion fisica
	keypad->id.bustype = BUS_HOST;  //tipo de bus
	keypad->id.vendor = 0x0010;
	keypad->id.product = 0x0001;
	keypad->id.version = 0x001;
	keypad->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	keypad->keycode = keypad_code;  //asignacion del arreglo del keycode
	keypad->keycodesize = sizeof(unsigned char);
	keypad->keycodemax = ARRAY_SIZE(keypad_code);

	for (i = 0; i <= 60; i++) { 
		set_bit(keypad_code[i], keypad->keybit);
	}

	error = input_register_device(keypad);
	if (error) {
		input_free_device(keypad);
		return error;
	}

        irq = gpio_to_irq(FPGA_IRQ_PIN);
        res = request_irq(irq, irq_handler, IRQF_DISABLED | IRQF_TRIGGER_RISING, "keypad", NULL); 
	return 0;
}

static void __exit skpad_exit(void)
{
	input_unregister_device(keypad);
	free_irq(irq, NULL);
}

module_init(skpad_init);
module_exit(skpad_exit);
