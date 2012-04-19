int main(void)
{
  volatile unsigned char    *data8;
  volatile unsigned short   *data16;
  volatile unsigned int     *data32;
  unsigned char             *no_volatile_data8;


/*
   Operaciones de acceso a memoria
*/
 
  data8  = (volatile unsigned char  *)(0x00000400);
  data16 = (volatile unsigned short *)(0x00000200);
  data32 = (volatile unsigned int   *)(0x00000300);

 
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

 
 
  data8              = (unsigned char volatile *)(0x00000400);
  no_volatile_data8  = (unsigned char  *)(0x00000800);

// Difference between volatile & no volatile

  *data8  = 0x44;
  *data8  = 0x45;
  *data8  = 0x46;
  *no_volatile_data8 = 0x64;
  *no_volatile_data8 = 0x65;
  *no_volatile_data8 = 0x66;



  while(1){
 
  }
  return 0;
}
