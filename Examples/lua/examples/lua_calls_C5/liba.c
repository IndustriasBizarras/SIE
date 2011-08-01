#include <stdio.h>  
#include <string.h>  
#include "liba.h"  
  
#define ENTER do{printf("in %s \n" ,__FUNCTION__);}while(0);  
  
void lib_a_f_1()  
{  
ENTER  
}  
  
int lib_a_f_2(int a , int b)  
{  
 ENTER  
 return a * b ;  
}  
  
  
int lib_a_f_3(const char *s)  
{  
    ENTER   
    return strlen(s);  
}  
  
int lib_a_f_4(Point *in_t)  
{  
   ENTER  
   return in_t->a * in_t->b ;  
}  
  
  
int lib_a_f_5(Point *out_t)  
{  
    ENTER  
    
    out_t->a = 20;   
    out_t->b = 30;  
  
    return 0;  
}  
