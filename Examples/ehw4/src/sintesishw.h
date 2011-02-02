/** Genetic definitions **/

#define HW_ENABLE	0	//habilitar hw, 0 se hace por SW
#define VARS 8
#define FUNCIONES 4
#define COMBS  (int) pow(2,VARS)
#define FUNCOMBS  (int) pow(FUNCIONES + 1, 3)
#define FUN_NOT 0
#define FUN_AND 1
#define FUN_XOR 2
#define FUN_OR 3
#define YES FUNCIONES
#define NOVAR VARS
#define PESO_SALIDA 1
#define PESO_PUERTAS 1

#define MAXGENERACIONES 32
#define RESULTADOS 4

/* Numero de generaciones en el que se amplia la logitud del cromosoma*/
#define UMBRAL_GENERACION (int) pow(3, pentarboles) * 5000
#define MAX_PENTARBOLES 16

#define POBLACION 4
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

#define INDICE_PADRE1 ((*ordenpoblacion) * LONG_INDIV)
#define INDICE_PADRE2 ((*(ordenpoblacion+1)) * LONG_INDIV)

#define INDICE_TARA1 ((*(ordenpoblacion+POBLACION-1)) * LONG_INDIV)
#define INDICE_TARA2 ((*(ordenpoblacion+POBLACION-2)) * LONG_INDIV)
#define INDICE_TARA3 ((*(ordenpoblacion+POBLACION-3)) * LONG_INDIV)
#define INDICE_TARA4 ((*(ordenpoblacion+POBLACION-4)) * LONG_INDIV)



/************************** peripheral Definitions ***************************/
#define EVALFIT_PHYSBASE 0xcd800000
#define USR_REGS  0x10
#define MAP_SIZE 0x4000Ul
#define MAP_MASK (MAP_SIZE - 1)

#define DONE_MASK 0x1
#define ERRORS_MASK 0xFFFF



/** CONTROL REGISTERS **/
#define EVALFIT_REGBASE_OFFSET 		0

#define EVALFIT_CONTROL_OFFSET 		EVALFIT_REGBASE_OFFSET + 0
#define CONTROL_RESET_MASK 0x80000000
#define CONTROL_START_MASK 0x40000000

#define EVALFIT_STATUS_OFFSET		EVALFIT_REGBASE_OFFSET + 0
#define EVALFIT_SRCADDR_OFFSET		EVALFIT_REGBASE_OFFSET + 4
#define EVALFIT_DSTADDR_OFFSET		EVALFIT_REGBASE_OFFSET + 8
#define EVALFIT_TRANSFERSIZE_OFFSET	EVALFIT_REGBASE_OFFSET + 12
#define EVALFIT_REG_OFFSET			EVALFIT_REGBASE_OFFSET + 16

/** WRITE REGISTERS **/
#define EVALFIT_WREG4		(EVALFIT_REGBASE_OFFSET + (4*4))
#define EVALFIT_WREG5		(EVALFIT_REGBASE_OFFSET + (4*5))
#define EVALFIT_wREG6		(EVALFIT_REGBASE_OFFSET + (4*6))
#define EVALFIT_wREG7		(EVALFIT_REGBASE_OFFSET + (4*7))
#define EVALFIT_wREG8		(EVALFIT_REGBASE_OFFSET + (4*8))

/** READ REGISTERS **/
#define EVALFIT_RDREG0		(EVALFIT_REGBASE_OFFSET)
#define EVALFIT_RDREG1		(EVALFIT_REGBASE_OFFSET + (4*1))
#define EVALFIT_RDREG2		(EVALFIT_REGBASE_OFFSET + (4*2))
#define EVALFIT_RDREG3		(EVALFIT_REGBASE_OFFSET + (4*3))
#define EVALFIT_RDREG4		(EVALFIT_REGBASE_OFFSET + (4*4))
#define EVALFIT_RDREG5		(EVALFIT_REGBASE_OFFSET + (4*5))
#define EVALFIT_RDREG6		(EVALFIT_REGBASE_OFFSET + (4*6))
#define EVALFIT_RDREG7		(EVALFIT_REGBASE_OFFSET + (4*7))

/** MEMORY **/
#define EVALFIT_MEMOFFSET 	0x1000
#define EVALFIT_OBJOFFSET 	EVALFIT_MEMOFFSET + (0x40 * 8)

/** CROMOSOMA **/
#define CROMO_NIVEL_OFFSET

