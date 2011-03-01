#include <stdio.h>
#include <unistd.h>
 
#include "jz47xx_gpio.h"
#include "jz47xx_mmap.h"
 
 #define CS2_PORT JZ_GPIO_PORT_B
 #define CS2_PIN  26
 #define RHR 0x00 /* Receive Holding Register */
 #define THR 0x00 /* Receive Holding Register */
 #define IER 0x01 /* Interrupt Enable Register */
 #define FCR 0x02 /* FIFO control Register       */
 #define ISR 0x02 /* Interrupt Status Register */
 #define LCR 0x03 /* Line control register    */
 #define MCR 0x04 /* Modem Control Register         */
 #define LSR 0x05 /* Line Status Register      */
 #define MSR 0x06 /* Modem Status Register          */
 #define SCR 0x07 /* Scratch pad Register        */
 /* This two offsets are used for defining the baud rate   */ 
 #define       DIVLSB                    0x00 /* Divisor LSB latch address */
 #define       DIVMSB                    0x01 /* Divisor MSB Latch address */
 


#include <stdio.h>
#include <unistd.h>

#include "jz47xx_gpio.h"
#include "jz47xx_mmap.h"

#define CS2_PORT JZ_GPIO_PORT_B
#define CS2_PIN  26
#define RHR 0x00 /* Receive Holding Register */
#define THR 0x00 /* Receive Holding Register */
#define IER 0x01 /* Interrupt Enable Register */
#define FCR 0x02 /* FIFO control Register       */
#define ISR 0x02 /* Interrupt Status Register */
#define LCR 0x03 /* Line control register    */
#define MCR 0x04 /* Modem Control Register         */
#define LSR 0x05 /* Line Status Register      */
#define MSR 0x06 /* Modem Status Register          */
#define SCR 0x07 /* Scratch pad Register        */
/* This two offsets are used for defining the baud rate   */
#define       DIVLSB                    0x00 /* Divisor LSB latch address */
#define       DIVMSB                    0x01 /* Divisor MSB Latch address */


int main () {
  
  JZ_PIO *pio;
  char *virt_addr, get_tecla, in, in2=0, in1=0;
  int i;
  pio = jz_gpio_map (CS2_PORT);
  jz_gpio_as_func (pio, CS2_PIN, 0);

virt_addr = (int *) jz_mmap (0x13010000) + 0x18;
 if (*virt_addr != 0xFFF7700)
    {                           // 0 WS, 8 bits
      *virt_addr = 0xFFF7700;
    //  printf ("Configuring CS2 8 bits \n");
    }
  else
    printf ("CS3, already configured\n");
  
  virt_addr = (JZ_REG *) jz_mmap (0x15000000);
   
  virt_addr[LCR]=0x80;//registros de configuracion de UART
  virt_addr[DIVMSB]=0x00;
  virt_addr[DIVLSB]=0x0C;
  virt_addr[LCR]=0x03;
  virt_addr[IER]= 0x01;



	  
	
		virt_addr[THR]=0x0f;//inicio de estados
		usleep(20000);
		virt_addr[THR]=0x0E;
		usleep(20000);
		virt_addr[THR]=0x01;
		usleep(20000);
		virt_addr[THR]=0x01;
		usleep(20000);
		for (i=0;i<48;i++)//registros de configuracion
			{virt_addr[THR]=0x28;
			usleep(20000);}
		for (i=0;i<48;i++)
			{virt_addr[THR]=0x4A;
			usleep(20000);}
		for (i=0;i<48;i++)
			{virt_addr[THR]=0x52;
			usleep(20000);}
		for (i=0;i<48;i++)
			{virt_addr[THR]=0x14;
			usleep(20000);}
		for (i=0;i<48;i++)
			{virt_addr[THR]=0xA6;
			usleep(20000);}
		virt_addr[THR]=0x11;
		usleep(20000);
		virt_addr[THR]=0x00;
		usleep(20000);
		virt_addr[THR]=0x64;
		usleep(20000);
		virt_addr[THR]=0x00;
		usleep(20000);
		virt_addr[THR]=0x6c;
		usleep(20000);
		virt_addr[THR]=0x00;
		usleep(20000);
		virt_addr[THR]=0x00;//fin de registros de configuracion
		usleep(20000);
		virt_addr[THR]=0x04;
		usleep(20000);
		virt_addr[THR]=0x04;
		usleep(20000);
		virt_addr[THR]=0x0f;
		usleep(20000);
		virt_addr[THR]=0x0e;//fin de estados finitos



			while (1){

				//recepcion de los registros enviados por el integrado

				virt_addr[THR]=0x06;
				in=virt_addr[THR];
				usleep(120000);

	
	
	


			}




}
