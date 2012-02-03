#include <stdio.h>
#include <unistd.h>
 
#include "jz47xx_gpio.h"
#include "jz47xx_mmap.h"
 
 #define CS2_PORT JZ_GPIO_PORT_B
 #define CS2_PIN  26
 
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
