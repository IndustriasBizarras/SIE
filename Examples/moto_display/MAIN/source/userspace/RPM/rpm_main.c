#include "stdio.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
      int            fileNum;
      unsigned char  buf[40];
      unsigned char  x;
  fileNum = open("/dev/rpm", O_RDWR);

  if (fileNum < 0) {
    printf(" Unable to open device\n");
    printf("fileNum = %i \n", fileNum);
    close(fileNum);
    exit(1);
  }

    printf("Device opened successfully \n");
    
    do {  
    read(fileNum, buf, sizeof(int));
    printf("rpm = %d \n",  *((int*)(buf)));
    printf("oprima x para volver a leer el dato de RPM \n");
    scanf("%c",&x);
    } while (x != "x");
    
    close(fileNum);
    
return (0);
}