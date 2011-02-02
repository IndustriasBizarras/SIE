#include "stdio.h"
#include "termios.h"
#include "sys/mman.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "time.h"
#include "math.h"
#include "pthread.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netdb.h"
#include "errno.h"
#include "sys/un.h"
#include "genetic.h"
#include "jz47xx_gpio.h"
#include <jz47xx_mmap.h>

#define CS2_PORT JZ_GPIO_PORT_B
#define CS2_PIN  26

/**************************************************************************************************************************************
	imprime un cromosoma completo */
void mostrar_indiv(char *cromo, int pentarboles, int vars)
{
char *ap, i, fn[8] = {'!', '&', '^', '|', '_'};	//NOT, AND, XOR, OR, NADA o YES
char vn[] = {'A', 'B', 'C', 'D', 'E' , 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', '.'};
char f1,f2,f3;
char a;

ap = cromo;

for(i = 0; i < ARBOLES_INDIV; i++){
		if(*(cromo + 7) == 1)
		{
			vn[vars] = '.';
			printf("%0x%c%c%c%c %i ", *(unsigned short int *)ap, vn[(*(ap+2) >> 4) & 0xF], vn[*(ap+2) & 0xF], vn[(*(ap+3) >> 4) & 0xF], vn[*(ap+3) & 0xF], *(ap+6));
		}
		else
		{
			vn[4] = '.';
			printf("%0x%c%c%c%c %i", *(unsigned short int *)ap, vn[(*(ap+2) >> 4) & 0xF], vn[*(ap+2) & 0xF], vn[(*(ap+3) >> 4) & 0xF], vn[*(ap+3) & 0xF], *(ap+6));
		}
//		printf("\t %0x %0x ", *(short int *)(ap+2), *(ap+6) );
	ap = ap + LONG_ARBOL;
}

printf(" ");
for(i = 0; i < LONG_INDIV; i++)
{	a=*(char *)(cromo+i) & 0xff;
	printf("%hhu,",a);
}
//fflush(stdout);
}

/**************************************************************************************************************************************
	imprime un arbol completo */
mostrar_arbol(char *cromo, int vars)
{
	char *ap, i, fn[8] = {'!', '&', '^', '|', '_'};	//NOT, AND, XOR, OR, NADA o YES
	char vn[] = {'A', 'B', 'C', 'D', 'E' , 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', '.'};
	ap = cromo;

		if(*(cromo + 7) == 1)
		{
			vn[vars] = '.';
			printf("LUT:%04x VARS:%c%c%c%c %0x", *(unsigned short int *)ap, vn[*(ap+2) >> 4], vn[*(ap+2) & 0xF], vn[*(ap+3) >> 4], vn[*(ap+3) & 0xF], *(ap+6));
		}
		else
		{
			vn[4] = '.';
			printf("LUT:%04x VARS:%c%c%c%c %0x", *(unsigned short int *)ap, vn[*(ap+2) >> 4], vn[*(ap+2) & 0xF], vn[*(ap+3) >> 4], vn[*(ap+3) & 0xF], *(ap+6));
		}
		printf("\tVARS:%04x \tLUT_index:%0x \t", *(unsigned short int *)(ap+2), *(ap+6) );
	for(i = 0; i < LONG_ARBOL; i++)
	{
		printf("%0x,",*(cromo+i));
	}
	printf("\n");
}

/**************************************************************************************************************************************
	genera un numero de forma aleatoria hasta max inclusive*/
char random_var(int max)
{
	char variable, mascara;
	int i;
	mascara = 1;
	do
	{
		mascara = (mascara << 1) + 1;
	}while(max > mascara);

	if(HW_ENABLE == 1)  variable = (*(int *)(evalfit_ptr1 + EVALFIT_RANDOM)) & mascara;
	else 				variable = random() & mascara;

	while(variable > max)
	{
		variable = variable - max;
	}
	return	variable;
}

/**************************************************************************************************************************************
	Genera un arbol de forma aleatoria
		Las funciones y variables son representadas por enteros del 0 al 3 o mas...
	- el arbol se encuentra compuesto de tres funciones, dos de entrada y una de salida.
*/
void gen_arbol(char *ap, int variables)
{
	int lut;
	short int dato_lut;
	lut = (random_var(FUNCIONES)*25) + (random_var(FUNCIONES) * 5) + random_var(FUNCIONES);//random_var(FUNCOMBS-1);
	dato_lut = (*(funlut_ap+(lut*2))  << 8) + (*(funlut_ap+(lut*2)+1));
	*(short int *)ap = ntohs(dato_lut); //Se cambia endianismo para cuando se ejecute en 386, que es distinto a PPC
	*(ap+2) = *(ap+3) = 0;
	*(ap+2) = random_var(variables) + (random_var(variables) << 4);
	*(ap+3) = random_var(variables) + (random_var(variables) << 4);
	*(ap+6) = lut;
//	mostrar_arbol(ap);
}


/**************************************************************************************************************************************
	genera un individuo de forma aleatoria */
void gen_indiv(char *cromo, int pentarboles, int vars)
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
	gen_arbol(cromo + (indice * LONG_ARBOL), vars-1);
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
	if((sig == 2) && (c2 < *(nivel2+pentarboles)))
	{
		gen_arbol(cromo + (indice*LONG_ARBOL), 3);
		*(cromo +(indice*LONG_ARBOL) + 7) = 2;
		n2++;
		c2 ++;
		indice ++;
		if(c2 == *(nivel2+pentarboles))
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
		if((sig == 3) && (c3 < *(nivel3+pentarboles)))
		{
			gen_arbol(cromo + (indice*LONG_ARBOL), 3);
			*(cromo +(indice*LONG_ARBOL) + 7) = 3;
			n3++;
			c3++;
			indice++;
			if(c3 == *(nivel3+pentarboles))
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
			if((sig == 4) && (c4 < *(nivel4+pentarboles)))
			{
				gen_arbol(cromo + (indice*LONG_ARBOL), 3);
				*(cromo +(indice*LONG_ARBOL) + 7) = 4;
				n4++;
				c4++;
				indice++;
				if(c4 == *(nivel4+pentarboles))
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
				if((sig == 5) && (c5 < *(nivel5+pentarboles)))
				{
					gen_arbol(cromo + (indice*LONG_ARBOL), 3);
					*(cromo +(indice*LONG_ARBOL) + 7) = 5;
					c5++;
					indice++;
					if(c5 == *(nivel5+pentarboles))
						sig = 1;
					else
						sig = 1;
				}
			}

		}
	}

}
/*    mostrar_indiv(cromo, 1,vars); //*/
}while(indice < ARBOLES_INDIV);

}


/**************************************************************************************************************************************
	genera una poblacion completa */
void gen_poblacion(char *cromo, int pentarboles, int vars, int indivs)
{
	int i;
	for(i=0; i < indivs; i++)
	{
		gen_indiv(cromo + ( i * LONG_INDIV), pentarboles, vars);
	}
}


/**************************************************************************************************************************************
	halla la salida de un arbol para una entrada de x de un cromo basado en LUT*/
int eval_func_lut(char *ap,  int x, int vars )	//var apunta al valor de las variables
{
char Y;
char var[vars], i, a, b, c, d;
int lut;

for(i=0;i <= vars-1;i++)
{
	var[i] = (x >> i) & 0x1;
//	printf("-%i",var[i]);
}
var[vars] = 0;

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
	retorna las salidas de un cromosoma de 5 arboles*/
void eval_pentarbol_sw(char *ap, int *salida, int *entrada, int vars)
{
	int i, k ;
	char salidas[ARBOLES][COMBS], aux[COMBS];

	for(i=0; i <= ARBOLES-2; i++){	//se evaluan las salidas de los primeros arboles y se almacenan en salidas
		for(k=0; k<= (COMBS-1); k++)
		{
			salidas[i][k] = eval_func_lut((ap+(i*LONG_ARBOL)), k, vars);
		}
	}

	//se calculan los minterminos para el arbol de salida
	for(k=0; k <= (COMBS-1); k++)
	{
		aux[k] = ((salidas[0][k])*1) + ((salidas[1][k])*2) + ((salidas[2][k])*4) + ((salidas[3][k])*8);
	}

	for(i=0; i <= (COMBS-1); i++)
	{
		*(salida + i) = eval_func_lut(ap + ((ARBOLES-1) * LONG_ARBOL), aux[i], vars);
	}
}


/**************************************************************************************************************************************
	retorna el numero de errores y las salidas de un cromosoma de 1 o mas pentarboles*/
int eval_fit_sw(char *ap, int *objetivo, int num_min, int pentarboles, int vars )
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
			eval_pentarbol_sw(ap + (i * LONG_ARBOL), salida, entrada, vars);
			for(j = 0; j < COMBS; j++)
			{
				*(med_min2 + j) = *(med_min2 + j) + (*(salida + j) << n2);
			}
			if(n2 == 3)	n2 = 0; else n2++;
			i = i + 5;
		}
 		else
		{
			if(*(ap + (i * LONG_ARBOL) + 7) == 3)
			{
				for(j = 0; j < COMBS; j++)
				{
					*(salida + j) = eval_func_lut(ap + (i * LONG_ARBOL), *(med_min2 + j), vars);
				}
				for(j = 0; j < COMBS; j++)
				{
					*(med_min3 + j) = *(med_min3 + j) + (*(salida + j) << n3);
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
						*(salida + j) = eval_func_lut(ap + (i * LONG_ARBOL), *(med_min3 + j), vars);
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
/*			printf("[%i]",*(med_min2 + j));*/
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
	inicia la evaluacion de un cromosoma en un periferico*/
int evalfit_hw_init(char *cromo, int pentarboles, int nivel_max, void *evalfit_ptr )
{
int i;

/** insertar cromosoma en periferico **/
    for(i = 0; i < ARBOLES_INDIV; i++)
    {
        *(int *)(evalfit_ptr + EVALFIT_MEMOFFSET + (LONG_ARBOL*i) + 0) =*(char *)(cromo +(LONG_ARBOL*i)+7);
        //printf("\n%04hhu: Level:%X ",  *(cromo+(i*LONG_ARBOL) + 6), *(int *)(evalfit_ptr + EVALFIT_MEMOFFSET + (LONG_ARBOL*i)  + 0));
        *(int *)(evalfit_ptr + EVALFIT_MEMOFFSET + (LONG_ARBOL*i) + 4) = *(int *)(cromo +(LONG_ARBOL*i));
        //printf("LUT-VARS: %08x",*(int *)(evalfit_ptr + EVALFIT_MEMOFFSET + (LONG_ARBOL*i) + 4));
    }
    *(int *)((evalfit_ptr) + EVALFIT_MEMOFFSET + (LONG_ARBOL*i) + 0) = 0xF;		//para terminar
    i++;
    *(int *)((evalfit_ptr) + EVALFIT_MEMOFFSET + (LONG_ARBOL*i) + 0) = 0xF;		//para terminar
/** Iniciar **/
    *(int *)(evalfit_ptr + EVALFIT_CONTROL_OFFSET) = CONTROL_START_MASK;
}

/**************************************************************************************************************************************
	espera y retorna el numero de errores y las salidas de un cromosoma de 1 o mas pentarboles*/
int evalfit_hw_wait(char *cromo, int pentarboles, int nivel_max, void *evalfit_ptr )
{
int errores, puertas, i;

   //	tiempo1 = get_timestamp();
    do{
        //printf("\nSTATUS: %0x",*(short *)(evalfit_ptr + EVALFIT_STATUS));
        //usleep(100);
    }while((*(short *)(evalfit_ptr + EVALFIT_STATUS) & DONE_MASK) != 0x8000);     //wait for DONE
    //tiempo2 = get_timestamp();
    //printf("\n\nErrors calculated HW: %0x",(*(int *)(evalfit_ptr + EVALFIT_ERRORS) & ERRORS_MASK));    //errores
    errores = (*(int *)(evalfit_ptr + EVALFIT_ERRORS) & ERRORS_MASK);        //errores
    *(int *)(evalfit_ptr + EVALFIT_CONTROL_OFFSET) = 0;                     //end , disable
    puertas = 0;
    for(i = 0; i < ARBOLES_INDIV; i++)
	{
		puertas = puertas +  *(puertas_ap + *(char *)(cromo +(LONG_ARBOL*i)+6));
	}
    return ((errores * PESO_SALIDA) + (PESO_PUERTAS * puertas) + (PESO_NIVELES * nivel_max));
}

/**************************************************************************************************************************************
	cruza dos cromosomas y almacena en destino. */
void cruzar(char *padre1, char *padre2, char *destino1, char *destino2, int pentarboles)
{
int a, i;

	a = (random() & 0x1F) + 1;	//punto de corte, es un numero de arbol

	while(a > (ARBOLES_INDIV))
	{
		a = a - ARBOLES_INDIV;//(pentarboles * ARBOLES);
	}
	a = a-1;
//	printf("\n%i",a);

	for(i = 0; i < (a * LONG_ARBOL); i++)
	{
		*(destino1 + i) = *(padre1 + i);	//padre1
		*(destino2 + i) = *(padre2 + i);	//padre1
	}

	for(i = (a * LONG_ARBOL); i < LONG_INDIV; i++)	// +1 para el arbol de salida
	{
		*(destino1 + i) = *(padre2 + i);	//padre2
		*(destino2 + i) = *(padre1 + i);	//padre2
	}
}

/**************************************************************************************************************************************
	cruza dos cromosomas y almacena en destino. */
void cross2point(char *padre1, char *padre2, char *destino1, char *destino2, int pentarboles)
{
int a, b, i;

	a = random_var((pentarboles*ARBOLES)-3);
	b = random_var((pentarboles*ARBOLES)-a-2)+a;
	a++;
	b++;
//	printf("\n%i %i %i",a,b,pentarboles*ARBOLES);fflush(stdout);
	for(i = 0; i < (a*LONG_ARBOL) ; i++)
	{
		*(destino1 + i) = *(padre1 + i);	//
		*(destino2 + i) = *(padre2 + i);	//
	}
	for(i = a; i < (b*LONG_ARBOL) ; i++)
	{
		*(destino2 + i) = *(padre1 + i);	//
		*(destino1 + i) = *(padre2 + i);	//
	}
	for(i = (b*LONG_ARBOL); i < LONG_INDIV; i++)	// +1 para el arbol de salida
	{
		*(destino1 + i) = *(padre1 + i);	//padre2
		*(destino2 + i) = *(padre2 + i);	//padre2
	}
}

/**************************************************************************************************************************************
	muta un cromosoma y almacena en destino. */

void muta_indiv(char *padre, char *destino,  int pentarboles, int vars)
{
	int a, i;

	gen_indiv(destino, pentarboles, vars);

	a = (random() & 0x1F) + 1;	//punto de corte, es un numero de arbol

	while(a > (ARBOLES_INDIV))
	{
		a = a - ARBOLES_INDIV;
	}

	for(i = 0; i < (a * LONG_ARBOL); i++)
	{
		*(destino + i) = *(padre + i);	//padre1
	}
}

/**************************************************************************************************************************************
        Introducir minterminos **/
void minterm2peripheral(int *fun_obj, int tamano, void *evalfit_ptr)
{
    int i, j, a;

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
     inicializar periferico **/
int init_peripheral(int offset_int, int basemem)
{
/* Variables para periferico*/
    int *aux, base_periferico, *ConfigRegsBase_ptr, maxcombs, nivel_max;
    void *pio, *evalfit_ptr;
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
return evalfit_ptr;
}

/**************************************************************************************************************************************
     cerrar periferico **/
int close_peripheral(char *evalfit_ptr)
{
	if(munmap(evalfit_ptr, MAP_SIZE)==-1)
		perror("munmap");
		printf("Error en unmap() (close_peripheral)\n");
		exit(-1);
}

/**************************************************************************************************************************************
     cambiar endianismo **/
int big2little(int x)
{
int y, i, r;
y=0;
r=0;
	for(i=0 ; i<=3; i++){
		x = x >> r;
		y = y << r;
		y = y | (x & 0xFF);
		r = 8;
	}
return y;
}

/**************************************************************************************************************************************
	crea y evoluciona un cromosoma a partir de una funcion objetivo*/
evolucionar(struct gen_datos_tipo *gen_datos)
{
int *generacion, k, a, i, j = 0, tamacromo, vars, aux, *aux_sal, T;
int conta=0, aux1, aux2, *fitness, *fitness2, *entrada, *objetivo, tamaobj, pentarboles, *fitness_sal, fitness_entrada, nivel_max;
char o, *ap, *cromo, *ordenpoblacion, *cromo_sal, *cromo_entrada;
long int tiempo1, tiempo2;
float tiempof1, tiempof2, tiempof3;

/* Variables para almacenar datos para graficar*/
	int *datos, x, puntos;
	char ruta[]="sarsar.dat";
	FILE *fich;
/*	datos = malloc(sizeof(datos)*maxgeneraciones*2);	if(datos==0) printf("Error en malloc");*/
/*	x=0;*/

    objetivo = gen_datos -> objetivo;
    tamaobj = gen_datos -> tamaobj;
    pentarboles = gen_datos -> pentarboles;
    tamacromo = gen_datos -> tamacrom;
    cromo_sal  = gen_datos -> cromo_sal;
    fitness_sal = gen_datos -> fitness;
    cromo_entrada  = gen_datos -> cromo_entrada;
    fitness_entrada  = gen_datos -> fitness_entrada;
    nivel_max = gen_datos -> nivel_max;
    vars = gen_datos -> vars;
    generacion = gen_datos->generacion;
    aux = gen_datos->aux;
    aux_sal = gen_datos->aux_sal;

    cromo = malloc(sizeof(cromo) * (poblacion + 2) * LONG_INDIV);	if(cromo==0) printf("Error en malloc");
    fitness = malloc(sizeof(fitness) * (poblacion+1));	if(fitness==0) printf("Error en malloc");
    fitness2 = malloc(sizeof(fitness2) * (poblacion+1)); if(fitness2==0) printf("Error en malloc");
    ordenpoblacion = malloc(sizeof(ordenpoblacion) * (poblacion+1)); if(ordenpoblacion==0) printf("Error en malloc");

    if(gen_datos->en_cromo_entrada == 1)
    {
        for(i = 0; i < LONG_INDIV; i++ )
        {
            *(char *)(cromo + i) = *(char *)(cromo_entrada + i);
        }
    }

    if(gen_datos->en_cromo_entrada == 0)
        gen_poblacion(cromo, pentarboles, vars, poblacion);     //generate chromosome
    else
        gen_poblacion(cromo + LONG_INDIV, pentarboles, vars, poblacion-1);

    for(i = 0; i < poblacion; i++)
    {
        *(ordenpoblacion + i) = i;	//se inicializa el stream para el orden poblacional
        *(fitness + i) = 100000;
        *(fitness2 + i) = 100000;
    }

/** copiar miniterminos a periferico **/
	if(HW_ENABLE == 1) {
		minterm2peripheral(objetivo, tamaobj, (int *)(evalfit_ptr1));
/*
	 	minterm2peripheral(objetivo, tamaobj, (int *)(evalfit_ptr2));
		minterm2peripheral(objetivo, tamaobj, (int *)(evalfit_ptr3));
		minterm2peripheral(objetivo, tamaobj, (int *)(evalfit_ptr4));
*/
	}

/** Insertar maxcombs y nivel_max **/
	if(HW_ENABLE == 1)	{
		*(int *)(evalfit_ptr1 + EVALFIT_WREG4) = (COMBS-1) + (nivel_max << 16);
/*
		*(int *)(evalfit_ptr2 + EVALFIT_WREG4) = (COMBS-1) + (nivel_max << 16);
		*(int *)(evalfit_ptr3 + EVALFIT_WREG4) = (COMBS-1) + (nivel_max << 16);
		*(int *)(evalfit_ptr4 + EVALFIT_WREG4) = (COMBS-1) + (nivel_max << 16);
*/
	}
	o=0;
	*generacion = 0;
    T = aux >> 16;
	do{

// cruzar
		for(i = ((poblacion*T)/8); i < ((poblacion*(T+1))/8); i=i+4)	//salvar los primeros 4 y cruzar
		{
			cross2point(cromo+INDICE_PADRE1, cromo+INDICE_PADRE2, cromo+(*(ordenpoblacion+i)*LONG_INDIV), cromo+(*(ordenpoblacion+i+1)*LONG_INDIV), pentarboles);
			cross2point(cromo+INDICE_PADRE1, cromo+INDICE_PADRE2, cromo+(*(ordenpoblacion+i+2)*LONG_INDIV), cromo+(*(ordenpoblacion+i+3)*LONG_INDIV), pentarboles);
		}//cruzar

// Mutacion
		for(i = ((poblacion*(T+1))/8); i < ((poblacion*(T+2))/8); i++)
		{
			muta_indiv(cromo + INDICE_PADRE1, cromo + ((*(ordenpoblacion + i )) * LONG_INDIV),  pentarboles, vars);
		}
		for(i = ((poblacion*(T+2))/8); i < ((poblacion*(T+3))/8); i++)
		{
			muta_indiv(cromo + INDICE_PADRE2, cromo + ((*(ordenpoblacion + i )) * LONG_INDIV),  pentarboles, vars);
		}

//crear nuevos indiv reemplazar por taras
		for(i = ((poblacion*(T+3))/8); i < poblacion; i++)
		{
			gen_indiv((cromo + ((*(ordenpoblacion + i)) * LONG_INDIV)), pentarboles, vars);
		}

// evaluar cromosomas de poblacion
		o=0;
//    tiempo1 = get_timestamp();
		for(i = 0; i < poblacion; i=i+1)
		{
			if(HW_ENABLE == 1)
			{
				evalfit_hw_init((cromo + (i * LONG_INDIV)), pentarboles, nivel_max, (int *)evalfit_ptr1);
/*
				evalfit_hw_init((cromo + ((i+1) * LONG_INDIV)), pentarboles, nivel_max, (int *)evalfit_ptr2);
				evalfit_hw_init((cromo + ((i+2) * LONG_INDIV)), pentarboles, nivel_max, (int *)evalfit_ptr3);
				evalfit_hw_init((cromo + ((i+3) * LONG_INDIV)), pentarboles, nivel_max, (int *)evalfit_ptr4);
*/
				*(fitness + i) = evalfit_hw_wait((cromo + (i * LONG_INDIV)), pentarboles, nivel_max, (int *)evalfit_ptr1);
/*
				*(fitness + i+1) = evalfit_hw_wait((cromo + ((i+1) * LONG_INDIV)), pentarboles,nivel_max, (int *)evalfit_ptr2);
				*(fitness + i+2) = evalfit_hw_wait((cromo + ((i+2) * LONG_INDIV)), pentarboles,nivel_max, (int *)evalfit_ptr3);
				*(fitness + i+3) = evalfit_hw_wait((cromo + ((i+3) * LONG_INDIV)), pentarboles, nivel_max, (int *)evalfit_ptr4);
*/
			}else{
				*(fitness + i) = eval_fit_sw((cromo + (i * LONG_INDIV)), objetivo, tamaobj, pentarboles, vars);
/*
				*(fitness + i+1) = eval_fit_sw((cromo + ((i+1) * LONG_INDIV)), objetivo, tamaobj, pentarboles, vars);
				*(fitness + i+2) = eval_fit_sw((cromo + ((i+2) * LONG_INDIV)), objetivo, tamaobj, pentarboles, vars);
				*(fitness + i+3) = eval_fit_sw((cromo + ((i+3) * LONG_INDIV)), objetivo, tamaobj, pentarboles, vars);
*/
			}
			*(fitness2 + i) = *(fitness + i);
/*
			*(fitness2 + i+1) = *(fitness + i+1);
			*(fitness2 + i+2) = *(fitness + i+2);
			*(fitness2 + i+3) = *(fitness + i+3);
*/

			if(*(fitness + i) < PESO_SALIDA)
			{
				o++;	//incrementar numero de aciertos
			}
		}
//    tiempo2 = get_timestamp();
        x++;

    //seleccionar cromosomas para mutar y cruzar y para eliminar, se realiza una ordenacion en ordenpoblacion, solo se ordena el indice del cromosoma
		for(i = 0; i < poblacion; i++)
		{
			*(ordenpoblacion + i) = i;	//se inicializa el stream para el orden poblacional
		}

		for(i=0; i < poblacion; i++)
		{
			for(j=i+1; j < poblacion; j++)
			{
				if(*(fitness2 + j) < *(fitness2 + i))
				{
					aux1 = *(ordenpoblacion + i);
					*(ordenpoblacion + i) = *(ordenpoblacion + j);
					*(ordenpoblacion + j) = aux1;
					aux2 = *(fitness2 + i);
					*(fitness2 + i) = *(fitness2 + j);
					*(fitness2 + j) = aux2;
				}
			}
		}


    //Se mide la evolucion del fitness en las generaciones, se saca la media por generacion
        aux1 = 0;
        for(i = 0; i < poblacion; i++)
        {
            aux1 = aux1 + *(fitness + i);
        }
        *(aux_sal + *generacion) = aux1 / poblacion;
        *(aux_sal + maxgeneraciones + *generacion) = *fitness2;

        (*generacion)++;

//	for(i=0; i < RESULTADOS; i++)
//	{
//		printf("\nfit%i: %i ", i, *(fitness+*(ordenpoblacion+i)), *(generacion+*(ordenpoblacion+i)));
//		mostrar_indiv(cromo + ( *(ordenpoblacion + i) * LONG_INDIV), pentarboles, vars);
//	}

	}while(/* (o < RESULTADOS) && */ (*generacion < maxgeneraciones));

	for(i = 0; i < RESULTADOS; i++)
	{
		for(j=0; j< LONG_INDIV;j++)
		{
			*(cromo_sal + (i*LONG_INDIV) + j) = *(cromo + (*(ordenpoblacion + i)*LONG_INDIV) + j);
		}
        *(fitness_sal + i) =  *(fitness + *(ordenpoblacion + i));
	}

	free(cromo);
	free(fitness);
	free(fitness2);
	free(ordenpoblacion);
}

