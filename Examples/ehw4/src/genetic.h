
/** Genetic definitions **/
#define HW_ENABLE	1	//cambiar en sintesishw_server.h   habilitar hw, 0 se hace por SW
#define PAR_ONLYFIT	0	//paralelizacion, 0 ALGORITMO ENTERO,  1 SOLO FITNESS

#define FUNCIONES 4
#define COMBS  (int) pow(2,vars)
#define FUNCOMBS  (int) pow(FUNCIONES + 1, 3)
#define FUN_NOT 0
#define FUN_AND 1
#define FUN_XOR 2
#define FUN_OR 3
#define YES FUNCIONES
#define NOVAR vars
#define PESO_SALIDA 100
#define PESO_PUERTAS 5
#define PESO_NIVELES 0

#define RESULTADOS 2

/* Numero de generaciones en el que se amplia la logitud del cromosoma*/
#define UMBRAL_GENERACION (int) pow(3, pentarboles) * 33
#define MAX_PENTARBOLES 16

#define ARBOLES 5
#define LONG_ARBOL 8

int nivel2[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int nivel3[]={0,0,1,1,1,2,2,2,2,3,3, 3, 3, 4, 4, 4};
int nivel4[]={0,0,0,0,0,1,1,1,1,1,1, 1, 1, 1, 1, 1};
int nivel5[]={0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0};

#define nivel1 pentarboles * 4
#define ARBOLES_INDIV (int)(nivel1 + *(nivel2+pentarboles) + *(nivel3+pentarboles) + *(nivel4+pentarboles) + *(nivel5+pentarboles))
#define LONG_INDIV (int)(ARBOLES_INDIV * LONG_ARBOL)

#define INDICE_PADRE1 ((*ordenpoblacion) * LONG_INDIV)
#define INDICE_PADRE2 ((*(ordenpoblacion+1)) * LONG_INDIV)

#define INDICE_TARA1 ((*(ordenpoblacion+poblacion-1)) * LONG_INDIV)
#define INDICE_TARA2 ((*(ordenpoblacion+poblacion-2)) * LONG_INDIV)
#define INDICE_TARA3 ((*(ordenpoblacion+poblacion-3)) * LONG_INDIV)
#define INDICE_TARA4 ((*(ordenpoblacion+poblacion-4)) * LONG_INDIV)


/************************** peripheral Definitions ***************************/

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

/*	Variables globales		*/
char *funlut_ap, *puertas_ap;
void *evalfit_ptr1, *evalfit_ptr4, *evalfit_ptr3, *evalfit_ptr2;
int maxgeneraciones, poblacion;


typedef long long timestamp_t;
static timestamp_t
		get_timestamp ()
{
	struct timeval now;
	gettimeofday (&now, NULL);
	return now.tv_usec + (timestamp_t)now.tv_sec *1000000 ;
}

struct gen_datos_tipo
{
	int *objetivo;
	int tamaobj;
	int pentarboles;
	int vars;
	int tamacrom;
	int maxgen;
	char *cromo_sal;
	int *fitness;
	char *cromo_entrada;
	int fitness_entrada;
	int nivel_max;
	int en_cromo_entrada;
	int *generacion;
	int *tiempo;
	int aux;
	int *aux_sal;
};

