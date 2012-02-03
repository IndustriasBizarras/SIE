#include "stdio.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
      int            fileNum;
      unsigned char  buf[1];
  
  fileNum = open("/dev/deb", O_RDWR);

  if (fileNum < 0) {
    printf(" Unable to open device\n");
    printf("fileNum = %i \n", fileNum);
    close(fileNum);
    exit(1);
  }

    printf("Device opened successfully \n");
    read(fileNum, buf, sizeof(int));
    printf("tecla presionada = %d \n",  *buf);
    close(fileNum);

return (0);
}
