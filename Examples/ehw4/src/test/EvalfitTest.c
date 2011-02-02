/***********************************************************************************************************
*   programa para hacer test perifericos evalfit del proyecto ehw4, con mersenne twister incorporado
*
*   Funciona con HW evalfit hasta con 14 vars. Evalfit funciona para 5 arboles. nivel max de 4.
*
************************************************************************************************************/

//	clk			=>	PLB_Clk,
//	reset		=>	regs_wr(0)(0),
//	habilita	=>	regs_wr(0)(1),
//	maxcombs 	=>	regs_wr(4)(16 to 31),
//	nivel_max 	=>	regs_wr(4)(12 to 15),
//      peripheral_mem_in	=>	do_mem_usr,-- 64 bits
//	peripheral_mem_en	=>	en_mem_usr,
//      peripheral_mem_out	=>	di_mem_usr,	-- 64 bits
//	peripheral_mem_we 	=>	we_mem_usr,
//	peripheral_mem_addr	=>	addr_mem_usr, --9 bits
//	evalfit3_estado		=>	regs_rd(1)(8 to 15),
//	errores				=>  regs_rd(2)(16 to 31),
//	fin_ack 			=>	regs_rd(1)(31)	);


#include <stdio.h>
#include <termios.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <evalfit.h>
#include "jz47xx_gpio.h"
#include <jz47xx_mmap.h>

#define CS2_PORT JZ_GPIO_PORT_B
#define CS2_PIN  26

typedef long long timestamp_t;
static timestamp_t
		get_timestamp ()
{
	struct timeval now;
	gettimeofday (&now, NULL);
	return now.tv_usec + (timestamp_t)now.tv_sec *1000000 ;
}


int nivel2(int pentarboles)
{
int x;
	if(nivel1 > 1)
		x = (int)ceil((float)nivel1 / 4);
	else
		x = 0;
return x;

}
int nivel3(int pentarboles)
{
int x;
	if(nivel2(pentarboles) > 1)
		x = (int)ceil((float)nivel1 / 16);
	else
		x = 0;
return x;
}
int nivel4(int pentarboles)
{
int x;
	if(nivel3(pentarboles) > 1)
		x = (int)ceil((float)nivel1/ 64);
	else
		x = 0;
return x;
}
int nivel5(int pentarboles)
{
int x;
	if(nivel4(pentarboles) > 1)
		x = (int)ceil((float)nivel1 / 256);
	else
		x = 0;
return x;
}


/**************************************************************************************************************************************
	genera un numero de forma aleatoria*/
char random_var(int max)
{
	char variable, mascara;
	int i;
	mascara = 1;
	do
	{
		mascara = (mascara << 1) + 1;
	}while(max > mascara);
	variable = random() & mascara;

	while(variable > max)
	{
		variable = variable - max;
	}
	return	variable;
}

/**************************************************************************************************************************************
	imprime un cromosoma completo */
void mostrar_indiv_lut(char *cromo, int pentarboles)
{
	char *ap, i, fn[8] = {'!', '&', '^', '|', '_'};	//NOT, AND, XOR, OR, NADA o YES
	char vn[] = {'A', 'B', 'C', 'D', 'E' , 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', '.'};
	ap = cromo;

		if(*(cromo + 7) == 1)
		{
			vn[VARS] = '.';
			printf(": %0x%c%c%c%c", *(unsigned short int *)ap, vn[*(ap+2) >> 4], vn[*(ap+2) & 0xF], vn[*(ap+3) >> 4], vn[*(ap+3) & 0xF]);
		}
		else
		{
			vn[4] = '.';
			printf(": %0x%c%c%c%c", *(unsigned short int *)ap, vn[*(ap+2) >> 4], vn[*(ap+2) & 0xF], vn[*(ap+3) >> 4], vn[*(ap+3) & 0xF]);
		}
		printf("\t %0x %0x ", *(short int *)(ap+2), *(ap+6) );
	for(i = 0; i < LONG_ARBOL; i++)
	{
		printf("%0x,",*(cromo+i));
	}
//	printf("\n");
}


/**************************************************************************************************************************************
	imprime un cromosoma completo */
void mostrar_indiv(char *cromo, int pentarboles)
{
char *ap, i, fn[8] = {'!', '&', '^', '|', '_'};	//NOT, AND, XOR, OR, NADA o YES
char vn[] = {'A', 'B', 'C', 'D', 'E' , 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', '.'};

ap = cromo;
for(i = 0; i < ARBOLES_INDIV; i++){
	if(*(cromo + (i * LONG_ARBOL) + 7) == 1)
	{
		vn[VARS] = '.';
		printf(" %c%c%c%c%c%c%c", fn[*ap], fn[*(ap+1)], vn[*(ap+2)], vn[*(ap+3)], fn[*(ap+4)], vn[*(ap+5)], vn[*(ap+6)]);
	}
	else
	{
		vn[4] = '.';
		printf(" %c%c%c%c%c%c%c", fn[*ap], fn[*(ap+1)], vn[*(ap+2)], vn[*(ap+3)], fn[*(ap+4)], vn[*(ap+5)], vn[*(ap+6)]);
	}
	ap = ap + LONG_ARBOL;
}
printf("\t");
//for(i = 0; i < LONG_INDIV; i++)
//{
//	printf("%i,",*(cromo+i));
//}
printf("\n");
}

/**************************************************************************************************************************************
	imprime un cromosoma completo */
void mostrar_indiv2(char *cromo, int pentarboles)
{
char *ap, i, fn[8] = {'!', '&', '^', '|', '_'};	//NOT, AND, XOR, OR, NADA o YES
char vn[] = {'A', 'B', 'C', 'D', 'E' , 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', '.'};

ap = cromo;

	if(*(cromo + (i * LONG_ARBOL) + 7) == 1)
	{
		vn[VARS] = '.';
		printf(" %c%c%c%c%c%c%c", fn[*ap], fn[*(ap+1)], vn[*(ap+2)], vn[*(ap+3)], fn[*(ap+4)], vn[*(ap+5)], vn[*(ap+6)]);
	}
	else
	{
		vn[4] = '.';
		printf(" %c%c%c%c%c%c%c", fn[*ap], fn[*(ap+1)], vn[*(ap+2)], vn[*(ap+3)], fn[*(ap+4)], vn[*(ap+5)], vn[*(ap+6)]);
	}

printf("\n");
}


/**************************************************************************************************************************************
	Genera un arbol de forma aleatoria
		Las funciones y variables son representadas por enteros del 0 al 3 o mas...
	- el arbol se encuentra compuesto de tres funciones, dos de entrada y una de salida.
*/
void gen_arbol_lut(char *ap, int variables)
{
	int lut;
	short int dato_lut;
	lut = random_var(FUNCOMBS-1);
	dato_lut = (*(funlut_ap+(lut*2)) << 8) + (*(funlut_ap+(lut*2)+1));
	*(short int *)ap = dato_lut;
	*(ap+2) = *(ap+3) = 0;
	*(ap+2) = random_var(variables-1) + (random_var(variables-1) << 4);
	*(ap+3) = random_var(variables-1) + (random_var(variables-1) << 4);
	*(ap+6) = lut;(ap);
}


/**************************************************************************************************************************************
	Genera un arbol de forma aleatoria
	- estructura de un arbol:  FFVVFVV  F = funcion  	V = variable
		Las funciones y variables son representadas por enteros del 0 al 3 o mas...
	- el arbol se encuentra compuesto de tres funciones, dos de entrada y una de salida.
*/
void gen_arbol(char *ap, int variables)
{
	*ap = random_var((FUNCIONES));	//funcion de salida, no YES
	*(ap+1) = random_var(FUNCIONES);	//PRIMER ARBOL
	*(ap+2) = random_var(variables);
	*(ap+3) = random_var(variables);
	*(ap+4) = random_var(FUNCIONES);	//SEGUNDO ARBOL
	*(ap+5) = random_var(variables);
	*(ap+6) = random_var(variables);

}


/**************************************************************************************************************************************
	genera un individuo de forma aleatoria */
void gen_indiv(char *cromo, int pentarboles)
{
char i=0;
int n1, n2, n3, n4, n5, c1, c2, c3, c4, c5, sig, indice;
n1 = n2 = n3 = n4 = n5 = 0;
c1 = c2 = c3 = c4 = c5 = 0;
indice = 0;

sig=1;


do
{

if((sig == 1) && (c1 < nivel1))
{
	gen_arbol(cromo + (indice * LONG_ARBOL), VARS-1);
	*(cromo +(indice*LONG_ARBOL) + 7) = 1;
	n1 ++;
	c1 ++;
	indice ++;
	if(n1 < 4)
		sig = 1;
	else
	{
		sig = 2;
		n1 = 0;
	}//printf("1");
}
else
{
	if((sig == 2) && (c2 < nivel2(pentarboles)))
	{
		gen_arbol(cromo + (indice*LONG_ARBOL), 3);
		*(cromo +(indice*LONG_ARBOL) + 7) = 2;
		n2++;
		c2 ++;
		indice ++;
		if(c2 == nivel2(pentarboles))
			sig = 3;
		else
		{
			if(n2 < 4)
				sig = 1;
			else
			{
				sig = 3;
				n2 = 0;
			}
		}//printf("2");
	}
	else
	{
		if((sig == 3) && (c3 < nivel3(pentarboles)))
		{
			gen_arbol(cromo + (indice*LONG_ARBOL), 3);
			*(cromo +(indice*LONG_ARBOL) + 7) = 3;
			n3++;
			c3++;
			indice++;
			if(c3 == nivel3(pentarboles))
				sig = 4;
			else
			{
				if(n3 < 4)
					sig = 1;
				else
				{
					sig = 4;
					n3 = 0;
				}
			}//printf("3");
		}
		else
		{
			if((sig == 4) && (c4 < nivel4(pentarboles)))
			{
				gen_arbol(cromo + (indice*LONG_ARBOL), 3);
				*(cromo +(indice*LONG_ARBOL) + 7) = 4;
				n4++;
				c4++;
				indice++;
				if(c4 == nivel4(pentarboles))
					sig = 5;
				else
				{
					if(n4 < 4)
						sig = 1;
					else
					{
						sig = 5;
						n4 = 0;
					}
				}//printf("4");
			}
			else
			{
				if((sig == 5) && (c5 < nivel5(pentarboles)))
				{
					gen_arbol(cromo + (indice*LONG_ARBOL), 3);
					*(cromo +(indice*LONG_ARBOL) + 7) = 5;
					c5++;
					indice++;
					if(c5 == nivel5(pentarboles))
						sig = 1;
					else
						sig = 1;
				}
			}

		}
	}

}

}while(indice < ARBOLES_INDIV);

}

/**************************************************************************************************************************************
	halla la salida de un arbol para una entrada de x de un cromo basado en LUT*/
int eval_func_lut(char *ap,  int x )	//var apunta al valor de las variables
{
char Y;
char var[VARS], i, a, b, c, d;
int lut;

for(i=0;i <= VARS-1;i++)
{
	var[i] = (x >> i) & 0x1;
//	printf("-%i",var[i]);
}
var[VARS] = 0;

a = *(ap + 3) & 0xF;
b = (*(ap + 3) >> 4) & 0xF;
c = *(ap + 2) & 0xF;
d = (*(ap + 2) >> 4) & 0xF;
i = var[a] + (var[b]*2) + (var[c]*4) + (var[d]*8);
lut = *(short int *)ap;
Y = (lut >> i) & 0x1;
return Y;
}

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
//	printf("-%i",var[i]);
}
var[VARS] = 0;

	f1 = 2*apfun[((*(ap+1))*4) + (2* (*(var+(*(ap+2))))) + *(var+(*(ap+3))) + 1];
//					^2da funcion		^1ra variable			^2da variable
	f2 = apfun[((*(ap+4))*4) + (2* (*(var+(*(ap+5))))) + *(var+(*(ap+6))) + 1];
//					^3ra funcion				^3ra variable			^4da variable
	Y = apfun[((*(ap))*4) + f1 +  f2   + 1];
//					^1ra funcion
//	printf("\n");

return Y;
}



/**************************************************************************************************************************************
	retorna las salidas de un cromosoma de 5 arboles*/
void eval_pentarbol_sw(char *ap, int *salida, int *entrada)
{
	int i, k ;
	char salidas[ARBOLES][COMBS], aux[COMBS];
	for(i=0; i <= ARBOLES-2; i++){	//se evaluan las salidas de los primeros arboles y se almacenan en salidas
		for(k=0; k<= (COMBS-1); k++)
		{
			salidas[i][k] = eval_func_lut((ap+(i*LONG_ARBOL)), k);
                }
	}

	//se calculan los minterminos para el arbol de salida
	for(k=0; k <= (COMBS-1); k++)
	{
		aux[k] = ((salidas[0][k])*1) + ((salidas[1][k])*2) + ((salidas[2][k])*4) + ((salidas[3][k])*8);
	}

	for(i=0; i <= (COMBS-1); i++)
	{
		*(salida + i) = eval_func_lut(ap + ((ARBOLES-1) * LONG_ARBOL), aux[i]);
	}
}


/**************************************************************************************************************************************
	retorna el numero de errores y las salidas de un cromosoma de 1 o mas pentarboles*/
int eval_fit_sw(char *ap, int *objetivo, int num_min, int pentarboles )
{
	int *obj_min, *med_min2, *med_min3, *med_min4, *med_min5, *entrada, i, j, errores, puertas;
	int *salida, n2, n3, n4, n5, x;

	obj_min = malloc(sizeof(obj_min)*COMBS);
	med_min2 = malloc(sizeof(med_min2)*COMBS);
	med_min3 = malloc(sizeof(med_min3)*COMBS);
	med_min4 = malloc(sizeof(med_min4)*COMBS);
	med_min5 = malloc(sizeof(med_min5)*COMBS);
	entrada = malloc(sizeof(entrada)*COMBS);
	salida =  malloc(sizeof(salida)*COMBS);
	errores = 0;

	for(i=0; i < COMBS; i++)
	{
		*(obj_min+i) = 0;
		*(entrada+i) = i;
		*(med_min2 + i) = 0;
		*(med_min3 + i) = 0;
		*(med_min4 + i) = 0;
		*(med_min5 + i) = 0;
	}

	for(i = 0; i < num_min; i++)
	{
		*(obj_min + (*(objetivo + i))) = 1;		//se convierte el objetivo a un arreglo
	}
	
	i = 0;
	n2 = 0;
	n3 = 0;
	n4 = 0;
	n5 = 0;
	
	do
	{
		if(*(ap + (i * LONG_ARBOL) + 7) == 1)
		{
			eval_pentarbol_sw(ap + (i * LONG_ARBOL), salida, entrada);
			for(j = 0; j < COMBS; j++)
			{
				*(med_min2 + j) = *(med_min2 + j) + (*(salida + j) << n2);
//				printf("%i ",*(med_min2 + j));////////quitar
			}
			if(n2 == 3)	n2 = 0; else n2++;
			i = i + 5;
//			printf("    ");////////quitar
		}
 		else
		{
			if(*(ap + (i * LONG_ARBOL) + 7) == 3)
			{
				for(j = 0; j < COMBS; j++)
				{
					*(salida + j) = eval_func_lut(ap + (i * LONG_ARBOL), *(med_min2 + j));
				}
				for(j = 0; j < COMBS; j++)
				{
					*(med_min3 + j) = *(med_min3 + j) + (*(salida + j) << n3);
//					printf("%i ",*(med_min3 + j));////////quitar
				}
				if(n3 == 3)	n3 = 0; else n3++;
				i++;
			}
			else
			{
		
				if(*(ap + (i * LONG_ARBOL) + 7) == 4)
				{
					for(j = 0; j < COMBS; j++)
					{
						*(salida + j) = eval_func_lut(ap + (i * LONG_ARBOL), *(med_min3 + j));
					}
					for(j = 0; j < COMBS; j++)
					{
						*(med_min4 + j) = *(med_min4 + j) + (*(salida + j) << n4);
					}
					if(n4 == 3)	n4 = 0; else n4++;
					i++;
				}
			}
		}
	}while(i <= (ARBOLES_INDIV-1));

	if(*(ap + ((ARBOLES_INDIV-1) * LONG_ARBOL) + 7) == 2)
	{
		for(j = 0; j < COMBS; j++)		//se evalua el arbol de salida
		{
			errores = errores + abs(*(med_min2 + j) - *(obj_min + j));		//errores
		}
	}
	
	if(*(ap + ((ARBOLES_INDIV-1) * LONG_ARBOL) + 7) == 3)
	{
		for(j = 0; j < COMBS; j++)		//se evalua el arbol de salida
		{
			errores = errores + abs(*(med_min3 + j) - *(obj_min + j));		//errores
		}
	}
	
	if(*(ap + ((ARBOLES_INDIV-1) * LONG_ARBOL) + 7) == 4)
	{
		for(j = 0; j < COMBS; j++)		//se evalua el arbol de salida
		{
			errores = errores + abs(*(med_min4 + j) - *(obj_min + j));		//errores
		}
	}
	
	if(*(ap + ((ARBOLES_INDIV-1) * LONG_ARBOL) + 7) == 5)
	{
		for(j = 0; j < COMBS; j++)		//se evalua el arbol de salida
		{
			errores = errores + abs(*(med_min5 + j) - *(obj_min + j));		//errores
		}
	}
	free(obj_min);
	free(med_min2);
	free(med_min3);
	free(med_min4);
	free(med_min5);
	free(entrada);
	free(salida);

	puertas = 0;
	
	return ((errores * PESO_SALIDA) + puertas);
}

/**************************************************************************************************************************************
	Introducir minterminos **/
void minterm2peripheral(int *fun_obj, int tamano)
{   int i, j, a;

	for(i = 0; i < 512; i++)	//rellenar con 0
	{
		*(int *)(evalfit_ptr + EVALFIT_OBJOFFSET + (i*4)) = 0;
	}

	for(i = 0; i < tamano; i++)      //insertar 1's en segmento de mem objetivo
	{
		j=0;
		a=fun_obj[i];
		while(a > 31)
		{
			a -= 32;
			j++;
		}
		*(int *)(evalfit_ptr + EVALFIT_OBJOFFSET + (j*4)) += (1 << (31-a));
	}
}
/*************************************************************************************************************************************/


/**************************************************************************************************************************************
    map peripheral **/
int periph_map(off_t offset)
{
int basemem, baseperiph;
	basemem = open("/dev/mem", (O_RDWR | O_SYNC));  //abrir dispositivo memoria para mapear dir del periferico
	if(basemem == -1)
	{
		printf("Error to open /dev/mem \n");
		return -1;
	}
	baseperiph = (int )mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, basemem, offset);// & ~MAP_MASK);
	if (baseperiph == -1)
	{
		printf ("Cannot mmap.\n");
		return -1;
	}
return baseperiph;
}


/**************************************************************************************************************************************
main **/
int main()
{
    int *aux, base_periferico, *ConfigRegsBase_ptr, basemem, maxcombs, nivel_max;
    int a, b, c, i,j, pentarboles, sum1, sum2, sum3;
    long int tiempo1, tiempo2;
    char *cromo, *cromo2, *obj;
    short int dato_lut;
    int fun_obj[16];
    void *pio;
    
    for(i=0;i<16;i++)
    {
            fun_obj[i] = i;
    }

/** Variables para tablas de lut **/
    FILE *f1;
    int size1;

    srand ( (time(NULL)) );

    cromo = malloc(sizeof(char) * LONG_ARBOL*21);
    if(cromo==0) printf("Error en malloc");
    cromo2 = malloc(sizeof(char) * LONG_ARBOL*21);
    if(cromo2==0) printf("Error en malloc");
    obj = malloc(COMBS);
    if(obj==0) printf("Error en malloc");
    a= sizeof(fun_obj)/4;
    printf("{%0x %0x}",a,COMBS);

    for(i=0;i<a;i++)
    {
            *(obj + fun_obj[i]) = 1;
    }

/** Tabla para las LUT **/
    f1 = fopen("funlut.dat","r");
    if(f1 == NULL){
            printf("\nError de lectura de archivo!");
            return 0;}
    fseek (f1, 0, SEEK_END);
    size1 = ftell(f1);
    funlut_ap = malloc(size1);

    if(funlut_ap==0) printf("Error en malloc");
    rewind (f1);
    fread(funlut_ap,1,size1,f1);
    fclose(f1);


/** periferico **/
    printf("Evalfit Test...");
    basemem = open("/dev/mem", (O_RDWR | O_SYNC));  //abrir dispositivo memoria para mapear dir del periferico
    if(basemem == -1)
    {
            printf("Error al abrir /dev/mem \n");
            return -1;
    }
    pio = jz_gpio_map(CS2_PORT);
    jz_gpio_as_func (pio, CS2_PIN, 0);
    ConfigRegsBase_ptr = (int *)periph_map(CONFIG_REGS_BASE);// + SACR2_OFFSET/sizeof(int);//SMCR2_OFFSET/sizeof(int);
    printf("\n%0x ", *(ConfigRegsBase_ptr + SMCR2_OFFSET/sizeof(int)));
    munmap(ConfigRegsBase_ptr, MAP_SIZE);
    evalfit_ptr = (int *)periph_map(EVALFIT_PHYSBASE1);

    printf("\r\nevalfit_ptr: %0x", evalfit_ptr);
    if( evalfit_ptr == (int *)MAP_FAILED)
    {   printf("error mmap!\n");
            fflush(stdout);
            return -1;
    }
    *(char *)(evalfit_ptr + EVALFIT_CONTROL_OFFSET) = CONTROL_RESET_MASK;    //reset
    //sleep(1);
    *(char *)(evalfit_ptr + EVALFIT_CONTROL_OFFSET) = 0;
    printf("\nDate + Status: %0x\n", *(char *)(evalfit_ptr + EVALFIT_STATUS));

/* pentarboles */
    maxcombs = COMBS;
    pentarboles = 4;
    nivel_max = 0x3;
    printf("\nVars:%i COMBS: %0xH LONG_ARBOL:%0xH LONG_INDIV:%0xH  ARBOLES_INDIV:%i\n", VARS, maxcombs, LONG_ARBOL , LONG_INDIV, ARBOLES_INDIV);

    gen_indiv(cromo2, pentarboles);
    mostrar_indiv(cromo2, pentarboles);

/******* convertir a formato de luts ******/
    for(i = 0; i < ARBOLES_INDIV; i++)
    {
        *(short int *)(cromo+(i*LONG_ARBOL)) = *(short int *)(funlut_ap + ( (*(cromo2 + (i*LONG_ARBOL)) * 25) +
        (*(cromo2+(i*LONG_ARBOL)+1)*5) + *(cromo2+(i*LONG_ARBOL)+4) ) *2 );
        *(cromo+(i*LONG_ARBOL) + 3) = *(cromo2+(i*LONG_ARBOL) + 2) + (*(cromo2+(i*LONG_ARBOL) + 3) << 4);
        *(cromo+(i*LONG_ARBOL) + 2) = *(cromo2+(i*LONG_ARBOL) + 5) + (*(cromo2+(i*LONG_ARBOL) + 6) << 4);
        *(cromo+(i*LONG_ARBOL) + 6) = (*(cromo2+(i*LONG_ARBOL)) * 25) + (*(cromo2+(i*LONG_ARBOL)+1)*5) + *(cromo2+(i*LONG_ARBOL)+4);
        *(cromo+(i*LONG_ARBOL) + 7) = *(cromo2+(i*LONG_ARBOL) + 7);
    }

/** copiar miniterminos a periferico **/
    minterm2peripheral(fun_obj, sizeof(fun_obj)/4);

/** Insertar maxcombs y nivel_max **/
    *(short *)(evalfit_ptr + EVALFIT_MAX_COMBS) = maxcombs-1;
    *(char *)(evalfit_ptr + EVALFIT_MAX_LEVEL) =  nivel_max;

/** insertar cromosoma en periferico **/
    printf("\nInserting chromosome in peripheral..."); fflush(stdout);
    for(i = 0; i < ARBOLES_INDIV; i++)
    {
        *(int *)(evalfit_ptr + EVALFIT_MEMOFFSET + (LONG_ARBOL*i) + 0) =*(char *)(cromo +(LONG_ARBOL*i)+7);
        printf("\n%04hhu: Level:%X ",  *(cromo+(i*LONG_ARBOL) + 6), *(int *)(evalfit_ptr + EVALFIT_MEMOFFSET + (LONG_ARBOL*i)  + 0));
        *(int *)(evalfit_ptr + EVALFIT_MEMOFFSET + (LONG_ARBOL*i) + 4) = *(int *)(cromo +(LONG_ARBOL*i));
        printf("LUT-VARS: %08x",*(int *)(evalfit_ptr + EVALFIT_MEMOFFSET + (LONG_ARBOL*i) + 4));
    }
    *(int *)((evalfit_ptr) + EVALFIT_MEMOFFSET + (LONG_ARBOL*i) + 0) = 0xF;		//para terminar
    i++;
    *(int *)((evalfit_ptr) + EVALFIT_MEMOFFSET + (LONG_ARBOL*i) + 0) = 0xF;		//para terminar

/** Iniciar HW **/
    *(char *)(evalfit_ptr + EVALFIT_CONTROL_OFFSET) = CONTROL_START_MASK;
    tiempo1 = get_timestamp();

    do{
        //printf("\nSTATUS: %0x",*(short *)(evalfit_ptr + EVALFIT_STATUS));
        //usleep(100);
    }while((*(short *)(evalfit_ptr + EVALFIT_STATUS) & DONE_MASK) != 0x8000);     //wait for DONE
    tiempo2 = get_timestamp();
    printf("\n\nErrors calculated HW: %0x",(*(int *)(evalfit_ptr + EVALFIT_ERRORS) & ERRORS_MASK));    //errores
    *(char *)(evalfit_ptr + EVALFIT_CONTROL_OFFSET) = 0;                //disable peripheral
    printf("\ndt_hw:%i microsegs\n", tiempo2 - tiempo1);

/** por SW **/
    tiempo1 = get_timestamp();
    a = eval_fit_sw(cromo, fun_obj, sizeof(fun_obj)/4, pentarboles);
    tiempo2 = get_timestamp();
    printf("\nErrors calculated SW: %0x", a);
    printf("\ndt_sw:%i microsegs\n", tiempo2 - tiempo1);

/* Mersenne twister test */
    printf("\n\nnumero aleatorio: %0x",(*(int *)(evalfit_ptr + EVALFIT_RANDOM)));    //random
    free(funlut_ap);
    free(cromo);
    free(cromo2);
    free(obj);
    close(basemem);
    munmap(base_periferico, MAP_SIZE);
    exit(0);
return 0;
}
