/* Driver Para UART tipo 8250 Implementada en FPGA.
 * Autor: amasprillav - Basado en 'Tiny TTY driver * * Copyright (C) 2002 Greg Kroah-Hartman' y algunas funciones de xuart7350 de la página
 * http://www.embeddedarm.com, también de http://lkml.org/lkml/2008/8/5/295 y de http://en.wikibooks.org/wiki/Serial_Programming/termios
 * Fecha: 6/11/2010
 * Sistemas Embebidos - UNAL 2010-II
 */

#define DEBUG 1
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <asm/mach-jz4740/gpio.h> 
#include <linux/serial.h>
#include <linux/serial_core.h>
#include <linux/delay.h> 

#define FPGA_BASE 0xB5000000
/*Registros de la UART*/
#define RHR 0x00 
#define THR 0x00 
#define IER 0x01 
#define FCR 0x02 
#define ISR 0x02 
#define LCR 0x03 
#define MCR 0x04 
#define LSR 0x05 
#define MSR 0x06 
#define SCR 0x07
/*Registros para la velocidad de transmisión*/
#define       DIVLSB                    0x00 //latch de las cifras más significativas
#define       DIVMSB                    0x01 //latch de las cifras menos significativas

#define FPGA_IRQ_PIN          JZ_GPIO_PORTC(15)
#define CS2_PIN               JZ_GPIO_PORTB(26)

struct uart_port port;

static const char driver_name[] = "ttyFPGA";
static const char tty_dev_name[] = "ttyFPGA";

static void fpga_putc(struct uart_port *port, unsigned char c){outb(c,FPGA_BASE);}

static irqreturn_t vuart_rxint(int irq,void *dev_id){
		tty_insert_flip_char(port.state->port.tty, inb(FPGA_BASE), TTY_NORMAL);
		tty_flip_buffer_push(port.state->port.tty);
		return IRQ_HANDLED;
	return IRQ_HANDLED;
}


static unsigned int fpga_tx_empty(struct uart_port *port){return 1;}

static void fpga_set_mctrl(struct uart_port *port, unsigned int mctrl){}

static unsigned int fpga_get_mctrl(struct uart_port *port){return TIOCM_CAR | TIOCM_DSR | TIOCM_CTS;}

static void fpga_stop_tx(struct uart_port *port){}

static void fpga_start_tx(struct uart_port *port){
	
	while(1){
		fpga_putc(port,port->state->xmit.buf[port->state->xmit.tail]);
		printk("enviado: %c\n",port->state->xmit.buf[port->state->xmit.tail]);
		//Ajustar la cola de la UART Al buffer
		port->state->xmit.tail=(port->state->xmit.tail+1)&(UART_XMIT_SIZE-1);
		port->icount.tx++;
		if(uart_circ_empty(&port->state->xmit))break;
	}
	
}
static void fpga_stop_rx(struct uart_port *port){}

static void fpga_enable_ms(struct uart_port *port){}

static void fpga_break_ctl(struct uart_port *port, int break_state){}

static int fpga_startup(struct uart_port *port){
	int res;
	printk("fpga_startup\n");
  	res = request_irq(port->irq, vuart_rxint,IRQF_TRIGGER_FALLING, "ttyFPGA",(void*)port);//IRQF_DISABLED |
	if(res){
		printk("No se pudo registrar el IRQ!\n");
		return res;
	}
	//Envío los registros de inicialización para la velocidad de transmisión y recepción, también el formato de datos...
	outb(0x80,FPGA_BASE+LCR);
	//acá lo coloco a 9600 baudios porque es la velocidad de transmisión (esto es temporal).
	outb(0x00,FPGA_BASE+DIVMSB);
	outb(0x0c,FPGA_BASE+DIVLSB);
	//registro para habilitar las interrupciones...
	outb(0x03,FPGA_BASE+LCR);
	outb(0xCF,FPGA_BASE+FCR);
	outb(0x0B,FPGA_BASE+MCR);
	outb(0x01,FPGA_BASE+IER);
	return 0;
}
static void fpga_shutdown(struct uart_port *port){free_irq(port->irq, (void*)port);}	

static void fpga_set_termios(struct uart_port *port,struct ktermios *termios,struct ktermios *old){}

static const char *fpga_type(struct uart_port *port){return "ttyfpga";}

static int fpga_request_port(struct uart_port *port){return 0;}

static void fpga_config_port(struct uart_port *port, int flags){
	if (flags & UART_CONFIG_TYPE)
               port->type = PORT_16550A;
}
static void fpga_release_port(struct uart_port *port){}

static int fpga_verify_port(struct uart_port *port, struct serial_struct *ser){return 0;}

static struct uart_ops fpga_uart_ops = {
	.tx_empty	= fpga_tx_empty,
	.set_mctrl	= fpga_set_mctrl,
	.get_mctrl	= fpga_get_mctrl,
	.stop_tx	= fpga_stop_tx,
	.start_tx	= fpga_start_tx,
	.stop_rx	= fpga_stop_rx,
	.enable_ms	= fpga_enable_ms,
	.break_ctl	= fpga_break_ctl,
	.startup	= fpga_startup,
	.shutdown	= fpga_shutdown,
	.set_termios	= fpga_set_termios,
	.type		= fpga_type,
	.release_port	= fpga_release_port,
	.request_port	= fpga_request_port,
	.config_port	= fpga_config_port,
	.verify_port	= fpga_verify_port,
};

static struct uart_driver fpga_driver = {
	.owner		= THIS_MODULE,
	.driver_name	= driver_name,
	.dev_name	= tty_dev_name,
	.major		= 240,
	.minor		= 0,
	.nr		= 2,
};
static int __init fpga_init (void){
	int ret;
	unsigned int irq;

        // Set GPIOB26 as part of External Memory Controller
        jz_gpio_set_function(CS2_PIN, JZ_GPIO_FUNC1);

	//registrar el driver
	ret = uart_register_driver(&fpga_driver);
	if (ret) {
		pr_err("%s: No se pudo registrar la UART!\n", driver_name);
		return ret;
	}
	//asignar el pin de IRQ al que está conectado a la FPGA (IRQ_F en el esquemático)
 	irq = gpio_to_irq(FPGA_IRQ_PIN);
	//insertar los valores del puerto
	port.membase=(u8*)FPGA_BASE;
	port.line = 0;
	port.ops = &fpga_uart_ops;
	port.flags = ASYNC_BOOT_AUTOCONF;
	port.type = PORT_16550A;
	port.irq = irq;
	ret = uart_add_one_port(&fpga_driver, &port);
	if (ret) {
		pr_err("%s: No se pudo agregar el puerto ttyFPGA0!\n", driver_name);
		uart_remove_one_port(&fpga_driver, &port);
		uart_unregister_driver(&fpga_driver);
		return ret;
	}

	printk ("%s: Modulo cargado...\n", driver_name);
	return 0;		
}

static void __exit fpga_exit (void){
	uart_remove_one_port(&fpga_driver, &port);
	uart_unregister_driver(&fpga_driver);
	printk ("%s: Modulo descargado...\n", driver_name);
}

MODULE_AUTHOR("amasprillav <amasprillav@unal.edu.co>");
MODULE_DESCRIPTION("Driver para UART tipo 8250 implementada en Verilog");
MODULE_LICENSE("GPL");

module_init(fpga_init);
module_exit(fpga_exit);
