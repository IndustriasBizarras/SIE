
/** Genetic definitions **/
#define PAR_ONLYFIT	0	//paralelizacion, 0 ALGORITMO ENTERO,  1 SOLO FITNESS

#define RESULTADOS 2

/* Numero de generaciones en el que se amplia la logitud del cromosoma*/

#define ARBOLES 5
#define LONG_ARBOL 8

#define nivel1 pentarboles * 4
#define ARBOLES_INDIV (int)(nivel1 + *(nivel2+pentarboles) + *(nivel3+pentarboles) + *(nivel4+pentarboles) + *(nivel5+pentarboles))
#define LONG_INDIV (int)(ARBOLES_INDIV * LONG_ARBOL)

//sockets defs
#define PORT 3550 /* El puerto que sera abierto */
#define BACKLOG 2 /* El numero de conexiones permitidas */
#define MAXDATASIZE 10000 /* El numero maximo de datos en bytes */
#define IP0 "192.168.254.101"
#define IP1 "192.168.0.6"
#define IP2 "192.168.0.7"
#define IP3 "192.168.0.8"
#define IP4 "192.168.0.9"
#define IP5 "192.168.0.10"
#define IP6 "192.168.0.11"
#define IP7 "192.168.0.12"

//#define IP0 "193.147.52.150"
//#define IP1 "193.147.52.139"

/*	Variables globales		*/
char *funlut_ap, *puertas_ap;
void *evalfit_ptr1, *evalfit_ptr4, *evalfit_ptr3, *evalfit_ptr2;
int maxgeneraciones, poblacion, nodos;

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
