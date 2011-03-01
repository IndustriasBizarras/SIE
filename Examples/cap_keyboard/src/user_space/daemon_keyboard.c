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
  unsigned char *virt_addr, get_tecla, in, in2=0, in1=0;
  int i;
  pio = jz_gpio_map (CS2_PORT);
  jz_gpio_as_func (pio, CS2_PIN, 0);
 
 virt_addr = (int *) jz_mmap (0x13010000) + 0x18;
 if (*virt_addr != 0xFFF7700)
    {                           // 0 WS, 8 bits
      *virt_addr = 0xFFF7700;
     // printf ("Configuring CS2 8 bits \n");
    }
  else
    printf ("CS3, already configured\n");
 
  virt_addr = (JZ_REG *) jz_mmap (0x15000000);
 
  virt_addr[LCR]=0x80;//registros de configuracion de UART
  virt_addr[DIVMSB]=0x00;
  virt_addr[DIVLSB]=0x0C;
  virt_addr[LCR]=0x03;
  virt_addr[IER]= 0x01;

			while (1){
 				virt_addr[THR]=0x06;
				usleep(60000);
				//printf("%d\n",virt_addr[RHR]);
				usleep(60000);
 		}
 }
