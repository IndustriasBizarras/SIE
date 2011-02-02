#include "plasma.h"

#define MemoryRead(A) (*(volatile unsigned long*)(A))
#define MemoryWrite(A,V) *(volatile unsigned long*)(A)=(V)


int main(void)
{
  volatile unsigned char    *data8;
  volatile unsigned short   *data16;
  volatile unsigned int     *data32;

  
  volatile unsigned char    test8; 
  volatile unsigned short   test16;
  volatile unsigned int     test32, tmp;
  volatile unsigned long    test64; 

/*
   Operaciones de acceso a memoria
*/

  data8  = (unsigned char  *)(0x20000410);
  data16 = (unsigned short *)(0x20000210);
  data32 = (unsigned int   *)(0x20000330);

  *data8  = 0x44;
  data8++;
  *data8  = 0x66;
  data8++;
  *data8  = 0x55;
  data8++;
  *data8  = 0x22;
  data8++;
  *data8  = 0x11;

  *data16 = 0x2020;
  data16++;
  *data16 = 0x2121;
  data16++;
  *data16 = 0x2222;
  data16++;

  *data32 = 0x30303030;
  data32++;
  *data32 = 0x31313131;


  test8  = *data8;
  test16 = *data16;
  test32 = *data32;
  data8 += 4;
  data16++;
  data32++;
  test8  = *data8;
  test16 = *data16;
  test32 = *data32;


  data32 = (unsigned int *)(0x20000000);
  *data32 = 0x55555555; 
  test32 = *data32;
  data32 = (unsigned int *)(0x20000020);
  test32 = *data32;


/*
   Operaciones aritméticas
*/

  
  test32 = test32 + test8;
  test32 = 0x11111111 + test32;
  test32 = 0x1111 + test32;
  test32 = test32 + *data32;

  test64 = test32 * test8;
  test64 = 0x11111111 * test32;
  test64 = 0x1111 * test32;
  test64 = test32 * *data32;

  


  while(1){
  
  }
  return 0;
}

