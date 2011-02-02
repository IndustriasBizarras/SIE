//evalfit.h

/************************** Constant Definitions ***************************/
/*
	VARS		numero de variables
	FUNCIONES 	funciones booleanas, aparte de la YES. 0=NOT, 1=AND, 2=XOR, 3=OR, 4=YES	. YES es obligatoria.
*/
#define VARS 4
#define FUNCIONES 4
#define COMBS  (int) pow(2,VARS)
#define FUNCOMBS  (int) pow(FUNCIONES + 1, 3)
#define COMBSLUT  16
//#define TAMA_ARBOL 16
//#define NIVEL_ARBOL_MASC 3
#define FUN_NOT 0
#define FUN_AND 1
#define FUN_XOR 2
#define FUN_OR 3
#define YES FUNCIONES
#define NOVAR VARS
#define PESO_SALIDA 1
#define PESO_PUERTAS 1
#define MAXGENERACIONES 10000
#define RESULTADOS 4

/* Numero de generaciones en el que se amplia la logitud del cromosoma*/
#define UMBRAL_GENERACION (int) pow(3, pentarboles) * 5000
#define MAX_PENTARBOLES 16
#define POBLACION 64
#define ARBOLES 5
#define LONG_ARBOL 8
/*
POBLACION 	define el numero de individuos. minimo 6. 2 padres 4 taras
ARBOLES		define el numero de arboles en un individuo. Cada arbol tiene 3 funciones 4 variables.
INDICES_XXX	define el desplazamiento de un individuo en el cromosoma completo de la poblacion, cromo
*/
#define nivel1 pentarboles * 4
#define ARBOLES_INDIV (int)(nivel1 + nivel2(pentarboles) + nivel3(pentarboles) + nivel4(pentarboles) + nivel5(pentarboles))
#define LONG_INDIV (int)(ARBOLES_INDIV * LONG_ARBOL)

/*	Variables globales		*/
char *funlut_ap;
void *evalfit_ptr;


/************************** Constant Definitions ***************************/

#define CONFIG_REGS_BASE        0x13010000
#define SMCR2_OFFSET            0x18
#define SACR2_OFFSET            0x38

#define EVALFIT_PHYSBASE1       0x14000000
#define MAP_SIZE                0x4000Ul
#define MAP_MASK                (MAP_SIZE - 1)

#define DONE_MASK               0x8000
#define ERRORS_MASK             0xFFFF

/** CONTROL REGISTERS **/
#define EVALFIT_REGBASE_OFFSET 	0x1000

#define EVALFIT_CONTROL_OFFSET 	EVALFIT_REGBASE_OFFSET + 0x1D
#define CONTROL_RESET_MASK      0x80
#define CONTROL_START_MASK      0x40

#define EVALFIT_REG_OFFSET	EVALFIT_REGBASE_OFFSET + 0

/** WRITE REGISTERS **/

#define EVALFIT_MAX_COMBS       EVALFIT_REGBASE_OFFSET + 0x1E
#define EVALFIT_MAX_LEVEL       EVALFIT_REGBASE_OFFSET + 0x1C


#define EVALFIT_WREG4		(EVALFIT_REGBASE_OFFSET + (4*4))
#define EVALFIT_WREG5		(EVALFIT_REGBASE_OFFSET + (4*5))
#define EVALFIT_wREG6		(EVALFIT_REGBASE_OFFSET + (4*6))
#define EVALFIT_wREG7		(EVALFIT_REGBASE_OFFSET + (4*7))
#define EVALFIT_wREG8		(EVALFIT_REGBASE_OFFSET + (4*8))

/** READ REGISTERS **/
#define EVALFIT_ERRORS          EVALFIT_REGBASE_OFFSET + 0x14
#define EVALFIT_RANDOM          EVALFIT_REGBASE_OFFSET + 0x18
#define EVALFIT_STATUS          EVALFIT_REGBASE_OFFSET + 0x16


#define EVALFIT_RDREG0		(EVALFIT_REGBASE_OFFSET)
#define EVALFIT_RDREG1		(EVALFIT_REGBASE_OFFSET + (4*1))
#define EVALFIT_RDREG2		(EVALFIT_REGBASE_OFFSET + (4*2))
#define EVALFIT_RDREG3		(EVALFIT_REGBASE_OFFSET + (4*3))
#define EVALFIT_RDREG4		(EVALFIT_REGBASE_OFFSET + (4*4))
#define EVALFIT_RDREG5		(EVALFIT_REGBASE_OFFSET + (4*5))
#define EVALFIT_RDREG6		(EVALFIT_REGBASE_OFFSET + (4*6))
#define EVALFIT_RDREG7		(EVALFIT_REGBASE_OFFSET + (4*7))
#define EVALFIT_RDREG8		(EVALFIT_REGBASE_OFFSET + (4*8))
/** MEMORY **/
#define EVALFIT_MEMOFFSET 	0x0
#define EVALFIT_OBJOFFSET 	EVALFIT_MEMOFFSET + (0x40 * 8)