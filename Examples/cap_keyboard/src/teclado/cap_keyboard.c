/*Atmel QT-60486 drivers
 *Sistemas Embebidos
 *UNAL
 *Authors: amasprillav,jsbuendiag,jamonsalveh
 *Year: 2010-II*/

#include <linux/module.h>       /* Needed by all modules */
#include <linux/kernel.h>       /* Needed for KERN_INFO */
#include <linux/ioport.h>
#include <linux/device.h>
#include <linux/interrupt.h>  /* We want an interrupt */
#include <linux/irq.h>        /* We want an interrupt */
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <asm/delay.h>
#include <asm/uaccess.h>  
#include <asm/io.h>
#include <linux/gpio.h>
#include <asm/mach-jz4740/gpio.h>
#include <linux/input.h>
#define FPGA_IRQ_PIN          JZ_GPIO_PORTC(15) //pin del irq
#define FPGA_BASE 	      0xB5000000 //direccion virtual base de la FPGA

MODULE_AUTHOR("amasprillav <amasprillav at unal dot edu dot co");
MODULE_DESCRIPTION("Atmel QT60486 Capacitive Keyboard Driver");
MODULE_LICENSE("GPL");

static unsigned int fn=0, anterior;//variables globales para indicar si la tecla fn ha sido oprimida 
//y para controlar que no se escriba una tecla mas de una vez respectivamente

//arreglo que posee el keycode de las teclas posibles
static unsigned int cap_keycode[] = {
	KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
	KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P,
	KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_BACKSPACE,
	KEY_ESC, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_EQUAL, KEY_ENTER,
	KEY_TAB, KEY_LEFTBRACE, KEY_RIGHTBRACE, KEY_COMMA, KEY_DOT, KEY_BACKSLASH, KEY_SLASH, KEY_APOSTROPHE, KEY_UP, KEY_SEMICOLON,
	KEY_LEFTSHIFT, KEY_RIGHTALT, KEY_LEFTALT, KEY_SPACE, KEY_RIGHTCTRL, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_MINUS, KEY_RIGHTALT
};

unsigned int irq;//variable global del numero del irq asignado

//funcion del codificador normal
static unsigned int keydecode(unsigned char valor){
	unsigned int salida;//variable la cual tiene el valor del keycode para ser usada en las demas funciones
	//codificador para cuando se oprime una tecla normalmente
	switch(valor){
		case 150:salida=KEY_Q;break;
		case 200:salida=KEY_W;break;
		case 170:salida=KEY_E;break;
		case 244:salida=KEY_R;break;
		case 22:salida=KEY_T;break;
		case 72:salida=KEY_Y;break;
		case 41:salida=KEY_U;break;
		case 119:salida=KEY_I;break;
		case 149:salida=KEY_O;break;
		case 203:salida=KEY_P;break;
		case 116:salida=KEY_A;break;
		case 169:salida=KEY_S;break;
		case 104:salida=KEY_D;break;
		case 54:salida=KEY_F;break;
		case 212:salida=KEY_G;break;
		case 138:salida=KEY_H;break;
		case 235:salida=KEY_J;break;
		case 181:salida=KEY_K;break;
		case 87:salida=KEY_L;break;
		case 9:salida=KEY_BACKSPACE;break;
		case 42:salida=KEY_ESC;break;
		case 247:salida=KEY_Z;break;
		case 55:salida=KEY_X;break;
		case 105:salida=KEY_C;break;
		case 139:salida=KEY_V;break;
		case 213:salida=KEY_B;break;
		case 180:salida=KEY_N;break;
		case 234:salida=KEY_M;break;
		case 8:salida=KEY_EQUAL;break;
		case 86:salida=KEY_ENTER;break;
		case 75:salida=KEY_TAB;break;
		case 21:salida=KEY_LEFTBRACE;break;
		case 245:salida=KEY_RIGHTBRACE;break;
		case 171:salida=KEY_COMMA;break;
		case 73:salida=KEY_DOT;break;
		case 23:salida=KEY_BACKSLASH;break;
		case 118:salida=KEY_SLASH;break;
		case 40:salida=KEY_APOSTROPHE;break;
		case 202:salida=KEY_UP;break;
		case 137:salida=KEY_LEFTSHIFT;break;
		case 215:salida=KEY_RIGHTALT;break;
		case 53:salida=KEY_LEFTALT;break;
		case 107:salida=KEY_SPACE;break;
		case 10:salida=KEY_RIGHTCTRL;break;
		case 84:salida=KEY_LEFT;break;
		case 182:salida=KEY_DOWN;break;
		case 232:salida=KEY_RIGHT;break;
		default: salida=0;break;
		}





return salida;
} 


//funcion del codificador FN
static unsigned int keydecodefn(unsigned char valor){
	unsigned int salida; //variable la cual tiene el valor del keycode para ser usada en las demas funciones
	//codificador para cuando se oprime una tecla una vez se ha oprimida la tecla FN
	switch(valor){
		case 150:salida=KEY_1;break;
		case 200:salida=KEY_2;break;
		case 170:salida=KEY_3;break;
		case 244:salida=KEY_4;break;
		case 22:salida=KEY_5;break;
		case 72:salida=KEY_6;break;
		case 41:salida=KEY_7;break;
		case 119:salida=KEY_8;break;
		case 149:salida=KEY_9;break;
		case 203:salida=KEY_P;break;
		case 116:salida=KEY_7;break;
		case 169:salida=KEY_8;break;
		case 104:salida=KEY_9;break;
		case 54:salida=KEY_0;break;
		case 212:salida=KEY_MINUS;break;
		case 138:salida=KEY_H;break;
		case 235:salida=KEY_4;break;
		case 181:salida=KEY_5;break;
		case 87:salida=KEY_6;break;
		case 9:salida=KEY_BACKSPACE;break;
		case 42:salida=KEY_ESC;break;
		case 247:salida=KEY_Z;break;
		case 55:salida=KEY_X;break;
		case 105:salida=KEY_C;break;
		case 139:salida=KEY_V;break;
		case 213:salida=KEY_B;break;
		case 180:salida=KEY_1;break;
		case 234:salida=KEY_2;break;
		case 8:salida=KEY_3;break;
		case 86:salida=KEY_ENTER;break;
		case 75:salida=KEY_TAB;break;
		case 21:salida=KEY_LEFTBRACE;break;
		case 245:salida=KEY_RIGHTBRACE;break;
		case 171:salida=KEY_COMMA;break;
		case 73:salida=KEY_DOT;break;
		case 23:salida=KEY_BACKSLASH;break;
		case 118:salida=KEY_0;break;
		case 40:salida=KEY_MINUS;break;
		case 202:salida=KEY_UP;break;
		case 137:salida=KEY_LEFTSHIFT;break;
		case 215:salida=KEY_RIGHTALT;break;
		case 53:salida=KEY_LEFTALT;break;
		case 107:salida=KEY_SPACE;break;
		case 10:salida=KEY_RIGHTCTRL;break;
		case 84:salida=KEY_LEFT;break;
		case 182:salida=KEY_DOWN;break;
		case 232:salida=KEY_RIGHT;break;
		default: salida=0;break;
		}


return salida;
} 




static struct input_dev *cap_keyboard;//estructura que define el dispositivo de entrada

static irqreturn_t irq_handler(int irq, void *dev_id){  //funcion que atiende las interrupciones y define las acciones a tomar

	  if(inb(FPGA_BASE)==anterior){	//condicional para deshabilitar la multiple lectura de una tecla    
		return IRQ_HANDLED;
	  }

	  else if(inb(FPGA_BASE)==85){	//condicional para evitar que se escriba algo del valor mandado por defecto del integrado
	  	anterior=inb(FPGA_BASE);	    
		return IRQ_HANDLED;
	  }


	else if (inb(FPGA_BASE)==148){	//condicional para activacion de la tecla FN

		input_sync(cap_keyboard);
		 anterior=inb(FPGA_BASE);		
		fn=1;
	   	return IRQ_HANDLED;}

	//condicional para evaluar la activacion de las teclas alt, alt gr, ctrl y shift
	else if ((inb(FPGA_BASE)==137) || (inb(FPGA_BASE)==215) || (inb(FPGA_BASE)==10) || (inb(FPGA_BASE)==53)){ 
		input_report_key(cap_keyboard,keydecode(inb(FPGA_BASE)),1);//funcion que detecta la tecla y la pone en 1 o 0 logico
		input_sync(cap_keyboard); //sincronizar el buffer tty con la ultima tecla oprimida
		anterior=inb(FPGA_BASE); //asignacion a la variable global de la ultima tecla oprimida
	    return IRQ_HANDLED; //retorno de interrupcion controlada
	  }

	else if(fn!=1) { //condicional para detectar la tecla ya sea en modo normal o con combinacion de ctrl, alt o shift		
		input_report_key(cap_keyboard,keydecode(inb(FPGA_BASE)),1);
	    	input_report_key(cap_keyboard,KEY_LEFTSHIFT,0);
	    	input_report_key(cap_keyboard,KEY_RIGHTALT,0);
	    	input_report_key(cap_keyboard,KEY_LEFTALT,0);
	    	input_report_key(cap_keyboard,KEY_RIGHTCTRL,0);
		input_report_key(cap_keyboard,keydecode(inb(FPGA_BASE)),0);
		input_sync(cap_keyboard);
		anterior=inb(FPGA_BASE);
	   	return IRQ_HANDLED;}

	//condicional que indica que hacer en el caso de haber oprimido FN y otra letra. La mayoria son numeros
	else if ((inb(FPGA_BASE)==41) ||(inb(FPGA_BASE)==119) ||(inb(FPGA_BASE)==149) ||(inb(FPGA_BASE)==235) ||(inb(FPGA_BASE)==181) ||(inb(FPGA_BASE)==87) ||(inb(FPGA_BASE)==180) ||(inb(FPGA_BASE)==234) ||(inb(FPGA_BASE)==8) ||(inb(FPGA_BASE)==118) ||(inb(FPGA_BASE)==40)){
	
		input_report_key(cap_keyboard,KEY_LEFTSHIFT,0);
	    	input_report_key(cap_keyboard,KEY_RIGHTALT,0);
	    	input_report_key(cap_keyboard,KEY_RIGHTCTRL,0);
	    	input_report_key(cap_keyboard,KEY_LEFTALT,0);
		input_report_key(cap_keyboard,keydecodefn(inb(FPGA_BASE)),1);
		input_report_key(cap_keyboard,keydecodefn(inb(FPGA_BASE)),0);
		input_sync(cap_keyboard);
		fn=0;
		anterior=inb(FPGA_BASE);
	   	return IRQ_HANDLED;}
	
	//condicional que indica que hacer en el caso de haber oprimido FN y otra letra. Estas son teclas que requieren de shift para ilustrarlas
	else 
	 	{input_report_key(cap_keyboard,KEY_LEFTSHIFT,1);
	    	input_report_key(cap_keyboard,KEY_RIGHTALT,0);
	    	input_report_key(cap_keyboard,KEY_RIGHTCTRL,0);
	    	input_report_key(cap_keyboard,KEY_LEFTALT,0);
		input_report_key(cap_keyboard,keydecodefn(inb(FPGA_BASE)),1);
		input_report_key(cap_keyboard,keydecodefn(inb(FPGA_BASE)),0);
	 	input_report_key(cap_keyboard,KEY_LEFTSHIFT,0);
		input_sync(cap_keyboard);
		fn=0;
		 anterior=inb(FPGA_BASE);
	   	return IRQ_HANDLED;}

	  return IRQ_HANDLED;
}

static int __init atakbd_init(void)//funcion de inicializacion del teclado
{
	int i, error,res;


	cap_keyboard = input_allocate_device(); // ubica memoria para el dispositivo de entrada
	if (!cap_keyboard)
		return -ENOMEM;

	cap_keyboard->name = "CAP Keyboard"; //asignacion de datos del teclado
	cap_keyboard->phys = "capkey/input0"; //direccion fisica
	cap_keyboard->id.bustype = BUS_HOST;//tipo de bus
	cap_keyboard->id.vendor = 0x0010;
	cap_keyboard->id.product = 0x0001;
	cap_keyboard->id.version = 0x001;

	cap_keyboard->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_REP);
	cap_keyboard->keycode = cap_keycode;//asignacion del arreglo del keycode
	cap_keyboard->keycodesize = sizeof(unsigned char);
	cap_keyboard->keycodemax = ARRAY_SIZE(cap_keycode);

	for (i = 0; i <= 60; i++) { //funcion que ubica las 48 teclas (keycode) en memoria
		set_bit(cap_keycode[i], cap_keyboard->keybit);
	}

	error = input_register_device(cap_keyboard);//indica al sistema el nuevo dispositivo de entrada
	if (error) {
		input_free_device(cap_keyboard);
		return error;
	}

        irq = gpio_to_irq(FPGA_IRQ_PIN);//asigna el numero del irq al pin fisico del procesador
  
        res = request_irq(irq, irq_handler, IRQF_DISABLED | IRQF_TRIGGER_RISING, "cap_keyboard", NULL); // asignar el valor del irq y la funcion que lo utiliza
	return 0;
}

static void __exit atakbd_exit(void)
{
	input_unregister_device(cap_keyboard);//libera los recursos utilizados por el dispositivo
	free_irq(irq, NULL);
}

module_init(atakbd_init);
module_exit(atakbd_exit);
