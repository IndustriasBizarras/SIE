/***************************************************************/
/*              Programa de prueba en espacio de usuario       */
/*                       para el modulo RPM                    */
/*                                                             */
/*                Universidad Nacional de Colombia             */
/*                                                             */
/*          Autores: Cesar Augusto Pantoja                     */
/*                   Felipe Andres Navarro                     */
/*                                                             */
/*          Proyecto: Dispositivo de informacion               */
/*                    para vehiculos automotores               */
/*                                                             */
/*       Descripción: Este programa lee el dato del modulo     */
/*                    RPM desde el espacio de usuario          */
/*                                                             */
/***************************************************************/

#include "stdio.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
      
  int  fileNum;
  unsigned char  buf[40];
  unsigned char  x;
  
  //el driver se maneja como un archivo (0_RDWR = lectura/escritura)
  fileNum = open("/dev/rpm", O_RDWR);

  if (fileNum < 0) {
    printf(" Unable to open device\n");
    printf("fileNum = %i \n", fileNum);
    close(fileNum);
    exit(1);
  }

    printf("Device opened successfully \n");
    
   //Lectura e impresion del dato obtenido por el driver
    read(fileNum, buf, sizeof(int));
    printf("rpm = %d \n",  *((int*)(buf)));
      
   //se cierra el driver 
    close(fileNum);
    
return (0);
}
