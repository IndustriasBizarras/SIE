/*********************************************************************************************************
**	Programa para generar los posibles datos que van en una LUT
** 	- Son 3 funciones por LUT
** 	- Son 5 posibles funciones. 	0 NOT, 1 AND, 2 XOR, 3 OR, 4 YES
** 
**
**
**
**********************************************************************************************************/
#include <stdio.h>
#include <termios.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#define FUNCIONES 5
#define FUNCOMBS  (int) pow(FUNCIONES, 3)
#define VARS 4
#define COMBS  (int) pow(2,VARS)

#define POBLACION 64
#define ARBOLES 5
#define LONG_ARBOL 8

/**************************************************************************************************************************************
	halla la salida de un arbol para una entrada de x */
int eval_func(char *ap,  int x )	//var apunta al valor de las variables
{
	char apfun[32] = {0, 0x1, 0x1,0x0,0x0,  0x0,0x0,0x0,0x1,  0x0,0x1,0x1,0x0,  0x0,0x1,0x1,0x1, 0x0,0x0,0x1,0x1};  //0=NOT,1=AND,2=XOR,3=OR,4=YES
	char apl0, apl11, apl12;
	char Y, f1, f2;
	char var[VARS], i;

	for(i=0;i <= VARS-1;i++)
	{
		var[i] = (x >> i) & 0x1;
	//printf("-%i",var[i]);
	}
	var[VARS] = 0;

	f1 = 2*apfun[((*(ap+1))*4) + (2* (*(var+(*(ap+2))))) + *(var+(*(ap+3))) + 1];
//					^2da funcion		^1ra variable			^2da variable
	f2 = apfun[((*(ap+4))*4) + (2* (*(var+(*(ap+5))))) + *(var+(*(ap+6))) + 1];
//					^3ra funcion				^3ra variable			^4da variable
	Y = apfun[((*(ap))*4) + f1 +  f2   + 1];
//					^1ra funcion
//	printf("f1:%i f2:%i Y:%i ",f1,f2,Y);
	return Y;
}

/**************************************************************************************************************************************
	imprime un cromosoma completo */
mostrar_indiv(char *cromo, int pentarboles)
{
	char *ap, i, fn[8] = {'!', '&', '^', '|', '_'};	//NOT, AND, XOR, OR, NADA o YES
	char vn[] = {'A', 'B', 'C', 'D', 'E' , 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', '.'};

	ap = cromo;
	for(i = 0; i < 1; i++){
			vn[VARS] = '.';
			printf(" %c%c%c%c%c%c%c", fn[*ap], fn[*(ap+1)], vn[*(ap+2)], vn[*(ap+3)], fn[*(ap+4)], vn[*(ap+5)], vn[*(ap+6)]);
	}
	printf("\n");
}


main()
{
char *cromo, *tabla,*puertas;
int  i, j, k, l, salida,x;
char ruta[]="funlut.dat";
char ruta2[]="puertas.dat";
short int *funlut_ap;
int size1;

tabla = malloc(sizeof(short int) * FUNCOMBS*4);
if(tabla==0) printf("Error en malloc");
puertas = malloc(sizeof(short int) * FUNCOMBS*4);
if(tabla==0) printf("Error en malloc");
cromo = malloc(sizeof(char) * FUNCOMBS);
if(cromo==0) printf("Error en malloc");

FILE *f1, *fich=fopen(ruta,"wb");
FILE *f2, *fich2=fopen(ruta2,"wb");

printf("COMBS%i ", FUNCOMBS);

for(i = 0; i < FUNCIONES; i++)
{
	for(j = 0; j < FUNCIONES; j++)
	{
		for(k = 0; k < FUNCIONES; k++)
		{
			x = 0;
			for(l = 0; l < COMBS; l++)
			{
				*(puertas + ((i*25) + (j*5) + k))=0;
				*cromo = i;	
				*(cromo+1) = j;
				*(cromo+2) = 0;
				*(cromo+3) = 1;
				*(cromo+4) = k;
				*(cromo+5) = 2;
				*(cromo+6) = 3;	
				salida = eval_func(cromo, l);
				printf("%i", salida);
				x = x + (salida << l);
				if(*cromo != 4)	
					(*(puertas + ((i*25) + (j*5) + k) ))++;
				if(*(cromo + 1) != 4)	
					(*(puertas + ((i*25) + (j*5) + k)))++;
				if(*(cromo + 4) != 4 && *cromo != 4)	
					(*(puertas + ((i*25) + (j*5) + k)))++;
			}
			*(tabla + ((i*25) + (j*5) + k)*2 + 1 ) = 0xFF & (x>>8); // se guarda con little endian, para JZ e intel.
			*(tabla + ((i*25) + (j*5) + k)*2 ) = 0xFF & x;          // intercambia estos dos para cambiar endianismo
			printf("  %i %04hX %4X", (i*25) + (j*5) + k, *(unsigned short *)(tabla + ((i*25) + (j*5) + k)*2), *(unsigned char *)(tabla + ((i*25) + (j*5) + k)*2 + 1));
			mostrar_indiv(cromo, 1);
		}
	}
}

fwrite((short int *)tabla, FUNCOMBS, sizeof(short int),fich); 
fclose(fich);
fwrite((char *)puertas, FUNCOMBS, sizeof(char),fich2); 
fclose(fich2);

f1 = fopen("funlut.dat","r");
if(f1 == NULL){
	printf("\nError de lectura de archivo!");
	return 0;}
fseek (f1, 0, SEEK_END);
size1 = ftell(f1);
funlut_ap = malloc(size1);
if(funlut_ap==0) printf("Error en malloc");
rewind (f1);
fread(funlut_ap,2,size1/(sizeof(short int)),f1);
fclose(f1);	
	for(i = 0; i < (size1/sizeof(short int)); i++)
printf("\n%0x : %0x ",i, *(unsigned short int*)(funlut_ap+i));
free(funlut_ap);

}
