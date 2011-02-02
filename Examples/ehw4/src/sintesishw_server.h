
/** Genetic definitions **/
#define HW_ENABLE	1	//cambiar en genetic.h habilitar hw, 0 se hace por SW

#define RESULTADOS 2

#define ARBOLES 5
#define LONG_ARBOL 8

#define nivel1 pentarboles * 4
#define ARBOLES_INDIV (int)(nivel1 + *(nivel2+pentarboles) + *(nivel3+pentarboles) + *(nivel4+pentarboles) + *(nivel5+pentarboles))
#define LONG_INDIV (int)(ARBOLES_INDIV * LONG_ARBOL)

#define EVALFIT_PHYSBASE1 0xcd800000
#define EVALFIT_PHYSBASE2 0xcd820000
#define EVALFIT_PHYSBASE3 0xcd840000
#define EVALFIT_PHYSBASE4 0xcd860000

//sockets defs
#define PORT 3550 /* El puerto que sera abierto */
#define BACKLOG 2 /* El numero de conexiones permitidas */
#define MAXDATASIZE 10000 /* El numero maximo de datos en bytes */

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

