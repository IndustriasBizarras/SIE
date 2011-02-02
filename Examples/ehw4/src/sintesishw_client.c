/*********************************************************************************************************
** Programa para probar la sintesis combinacional mediante programacion genetica,
** se usan sockets para repartir carga de trabajo a otros clientes
** Se usa periferico evalfit del proyecto ehw3
** se aceleran 5 arboles, que en el presente codigo se llama pentarbol
** compilar con math.h   -lm
** compilar con threads: -lpthread
** gcc sintesishw_client.c -lm -lpthread -o sintesishw_client_ppc
** ejecutar:
**      ./sintesishw_client_386 vars poblacion generaciones pentarboles sar.dat sar2.dat
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
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <sys/un.h>
#include <sintesishw_client.h>

/**************************************************************************************************************************************
	*/
create_connect_socket(char *addr, int *fd_ap)
{
	int fd;
	struct sockaddr_in input_addr;
	struct sockaddr_in server;
 	if (inet_aton(addr, &input_addr.sin_addr)==-1)
	{ perror("inet_aton");
      exit(-1);
	}

   	if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){
      printf("socket() error\n");
      exit(-1);
   	}

	server.sin_family = AF_INET;
   	server.sin_port = htons(PORT);
   	server.sin_addr = input_addr.sin_addr;
   	bzero(&(server.sin_zero),8);

   if(connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr))==-1)
	{
 //     printf("connect() error en %s\n",addr);
	  perror("connect");
      exit(-1);
   	}
/*	printf(".");*/
	*fd_ap = fd;
}


rx_cromo(int fd, void *data_socket_rx_ap, char *cromo_sal, int *fitness, int pentarboles, int *generacion, int *tiempo, int *aux_sal)
{
void *ap1;
int i, j, numbytes_rx;
int nivel2[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int nivel3[]={0,0,1,1,1,2,2,2,2,3,3, 3, 3, 4, 4, 4};
int nivel4[]={0,0,0,0,0,1,1,1,1,1,1, 1, 1, 1, 1, 1};
int nivel5[]={0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0};


	if ((numbytes_rx=recv(fd,data_socket_rx_ap,MAXDATASIZE,0)) == -1){
      printf("Error en recv() \n");
	  perror("recv");
      exit(-1);
   	}
	ap1 = data_socket_rx_ap;
/*	printf("Rx:%i ",ntohl(*(int *)ap1));*/
	ap1 = ap1 + 4;
	for(i=0; i < RESULTADOS ;i++)
	{
		for(j=0; j < LONG_INDIV ;j++)
		{
			*(cromo_sal + j + (LONG_INDIV*i)) = *(char *)ap1;
			ap1 ++;
		}
		*(fitness + i) = ntohl(*(int *)ap1) & 0xFFFF;
		*(generacion + i) = ntohl(*(int *)ap1) >> 16;
		ap1 = ap1 + 4;
		*(tiempo+i) = ntohl(*(int *)ap1);
		ap1 = ap1 + 4;
	}
    for(i = 0; i < maxgeneraciones*2 ;i++)
	{
        *(aux_sal + i) = ntohl(*(int *)ap1);
        ap1 = ap1 + 4;
	}
}

tx_cromo(struct gen_datos_tipo *gen_datos, int fd)
{
void *data_socket_tx_ap, *ap1;
int *objetivo, i, numbytes_tx;

	data_socket_tx_ap = malloc((gen_datos->tamaobj)*sizeof(int) + gen_datos->tamacrom + 0xFF);
	ap1= data_socket_tx_ap;

	*(int *)ap1	= htonl(gen_datos->tamaobj | (maxgeneraciones << 16));
	ap1 = ap1 + 4;
	objetivo = gen_datos->objetivo;
	for(i=0; i < (gen_datos->tamaobj); i++)
	{
		*(int *)ap1 = htonl(objetivo[i]);
		ap1 = ap1 + 4;
	}
	*(int *)ap1 = htonl(gen_datos->pentarboles | (gen_datos->vars << 16));
	ap1 = ap1 + 4;
	*(int *)ap1 = htonl(gen_datos->tamacrom | (poblacion << 16));
	ap1 = ap1 + 4;

	for(i = 0; i < (gen_datos->tamacrom); i++)
	{
		*(char *)(ap1) = *(char *)(gen_datos->cromo_entrada + i);
		ap1 = ap1 + 1;
	}

	*(int *)ap1 =  htonl(gen_datos->fitness_entrada);  //fitness de entrada?
	ap1 = ap1 + 4;
	*(int *)ap1 = htonl((gen_datos->en_cromo_entrada<<16) | gen_datos->nivel_max);
	ap1 = ap1 + 4;
	*(int *)ap1 =  htonl(gen_datos->aux);  //datos varios
	ap1 = ap1 + 4;
    *(int *)ap1 =  htonl(0xa55a9669);  //datos varios
	ap1 = ap1 + 4;
	numbytes_tx = ap1 - data_socket_tx_ap;
	send(fd, data_socket_tx_ap, numbytes_tx ,0); //enviar
	free(data_socket_tx_ap);

}



/**************************************************************************************************************************************
	crea una poblacion, y envia a placas para evolucionar */
iniciar_evol(struct gen_datos_tipo *gen_datos)
{
int *generacion, k, a, i, j = 0, vars;
int conta=0, aux1, aux2, *fitness, *fitness2, *entrada, *objetivo, tamaobj, pentarboles, maxgens, *fitness_sal, fitness_entrada, nivel_max, *aux_sal;
char o, *ap, *cromo, *ordenpoblacion, *cromo_sal, *cromo_entrada;
int *tiempo;
int nivel2[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int nivel3[]={0,0,1,1,1,2,2,2,2,3,3, 3, 3, 4, 4, 4};
int nivel4[]={0,0,0,0,0,1,1,1,1,1,1, 1, 1, 1, 1, 1};
int nivel5[]={0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0};

/* variables para sockets */
	int fds[8],fd1, fd2, fd3, fd4, fd5, fd6, fd7, fd8, numbytes_tx, numbytes_rx;    /* ficheros descriptores para sockets*/
	void *data_socket_rx_ap;
	char server[][16] = {IP0, IP1, IP2, IP3, IP4, IP5, IP6, IP7};

	pentarboles = gen_datos->pentarboles;
	vars = gen_datos->vars;
	generacion = gen_datos->generacion;
	tiempo =  gen_datos->tiempo;
	aux_sal = gen_datos->aux_sal;

	cromo = malloc(sizeof(cromo) * (poblacion + 2) * LONG_INDIV);	if(cromo==0) printf("Error en malloc");
	fitness = malloc(sizeof(fitness) * (poblacion+1));	if(fitness==0) printf("Error en malloc");
	fitness2 = malloc(sizeof(fitness2) * (poblacion+1));	if(fitness2==0) printf("Error en malloc");
	ordenpoblacion = malloc(sizeof(ordenpoblacion) * (poblacion+1));	if(ordenpoblacion==0) printf("Error en malloc");

	for(i=0; i < nodos; i++)							//enviar a nodos
	{
		create_connect_socket(server[i], &fds[i]);
	}

/* preparar socket para recibir */
	data_socket_rx_ap = malloc(10000);

if(PAR_ONLYFIT==1)
{
	gen_poblacion(cromo, pentarboles, vars);

	// cruzar
			for(i = ((poblacion*1)/8); i < ((poblacion*2)/8); i=i+4)	//salvar los primeros 4 y cruzar
			{
				cross2point(cromo+i*LONG_INDIV, cromo + i*LONG_INDIV, cromo+((i)*LONG_INDIV), cromo+((i+1)*LONG_INDIV), pentarboles);
				cross2point(cromo+i*LONG_INDIV, cromo + i*LONG_INDIV, cromo+((i+2)*LONG_INDIV), cromo+((i+3)*LONG_INDIV), pentarboles);
			}//cruzar

	// Mutacion
			for(i = ((poblacion*2)/8); i < ((poblacion*3)/8); i++)
			{
				muta_indiv(cromo + i*LONG_INDIV, cromo + ((( i )) * LONG_INDIV),  pentarboles, vars);
			}
			for(i = ((poblacion*3)/8); i < ((poblacion*4)/8); i++)
			{
				muta_indiv(cromo + i*LONG_INDIV, cromo + ((( i )) * LONG_INDIV),  pentarboles, vars);
			}

	//crear nuevos indiv reemplazar por taras
			for(i = ((poblacion*4)/8); i < poblacion; i++)
			{
				gen_indiv((cromo + ((( i)) * LONG_INDIV)), pentarboles, vars);
			}

			*generacion++;
}

	gen_datos->tamacrom = LONG_INDIV;

for(j=0;j<1;j++)
{
	for(i=0; i<nodos;i++)							//enviar a nodos
	{
		tx_cromo(gen_datos, fds[i]);
	}

	cromo_sal = gen_datos->cromo_sal;

	for(i=0; i<nodos;i++)		//recoger fitness o cromosomas resultantes
	{
		rx_cromo(fds[i], data_socket_rx_ap, cromo_sal+(LONG_INDIV*RESULTADOS*i), gen_datos->fitness+(RESULTADOS*i), pentarboles,generacion + (RESULTADOS*i),tiempo+(RESULTADOS*i), aux_sal+(maxgeneraciones*2*i));
	}

}

	free(cromo);
	free(fitness);
	free(fitness2);
	free(ordenpoblacion);
	free(data_socket_rx_ap);
	for(i=0; i<nodos;i++)	close(fds[i]);
}


/*******************************************************************************************************************************/
/*******************************************************************************************************************************/
/*******************************************************************************************************************************/
/*******************************************************************************************************************************/

int main( int argc, char** argv )
{
    int *generacion, k, a, b, z, i, j= 0, error, nivel_max, vars, *tiempo, poblacion_total, m, p, iteraciones, T;
    int conta=0, aux1, aux2, pentarboles, *fitness1, *fitness2, *entrada, *orderesult, aux, *aux_sal;
    char o, *ap, *valor_devuelto;;
    char *cromo_sal1, *cromo_sal2, *cromo_entrada;
    int tamaobj, objetivo[8192], obj_combs;//= {0,254,123,16,87,56,34,76,89,155,199};
    long int tiempo1, tiempo2;
    float tiempof, tiempof2, Tfloat, float1, float2;

    int nivel2[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int nivel3[]={0,0,1,1,1,2,2,2,2,3,3, 3, 3, 4, 4, 4};
    int nivel4[]={0,0,0,0,0,1,1,1,1,1,1, 1, 1, 1, 1, 1};
    int nivel5[]={0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0};

/* Estructuras para datos de cromosomas*/
    struct gen_datos_tipo data_struct1, data_struct2;
    struct gen_datos_tipo *data_struct_ap1, *data_struct_ap2;
    data_struct_ap1 = &data_struct1;
    data_struct_ap2 = &data_struct2;

/* Variables para tablas de lut*/
    FILE *f1;
    int size1;
    srand ( (time(NULL)) );

/* Variables para almacenar datos para graficar*/
    int *datos, *datos2, x, media=4, puntos;
    FILE *fich, *fich2;

    char output_file_name[128], output_file_fitness_name[128];
    sscanf(argv[1], "%i",&vars);
    sscanf(argv[2], "%i", &poblacion_total);
    sscanf(argv[3], "%i", &maxgeneraciones);
    sscanf(argv[4], "%i", &nodos);
    sscanf(argv[5], "%s", output_file_name);
    sscanf(argv[6], "%s", output_file_fitness_name);
    printf("\nvars: %i indivs:%i generations:%i nodos:%i ", vars, poblacion_total, maxgeneraciones, nodos);
    fflush(stdout);

    pentarboles = 1;	//MODIFIQUE NIVEL_MAX
    nivel_max = 2;
    poblacion = poblacion_total/nodos;
    m = 1;  //datos a migrar
    p = maxgeneraciones;//8;  //frecuencia de migracion
    T = 4;  //temperatura para crear nuevos indiv. A mayor T menor temperatura
	i=0;
	tamaobj=0;
    aux = (T << 16) | p;
    iteraciones = maxgeneraciones/p;
    maxgeneraciones = p;

    obj_combs = pow(2, (vars/2));

/*Armar funcion objetivo comparador*/			/* OJO, SE ESTÁN METIENDO VALORES DE 1EXX EN LAS LUT Y ESOS INDIVIDUOS AL PARECER QUEDAN MAL */
    for(a=0; a < obj_combs ;a++)
    {
        for(b=0; b < obj_combs ;b++)
        {
            if(a > b)z=1; if(a < b)z=2; if(a == b)z=4;
            if((z & 0x4) != 0 )
            {
                objetivo[tamaobj] = i;
                printf("%i ",objetivo[tamaobj]);
                tamaobj++;
            }
            i++;
        }
    }
//	printf("Tama:%i ",tamaobj);

/* Tabla para las LUT*/
    f1 = fopen("funlut.dat","r");
    if(f1 == NULL){
            printf("\nError de lectura de archivo!");
            return 0;}

    fseek (f1, 0, SEEK_END);
    size1 = ftell(f1);
    funlut_ap = malloc(size1);	if(funlut_ap==0) printf("Error en malloc");
    rewind (f1);
    fread(funlut_ap,1,size1,f1);
    fclose(f1);

    puntos = 16;	/*numero de puntos para la grafica*/
    datos = malloc(sizeof(datos)*puntos*3);	if(datos==0) printf("Error en malloc");
    fich=fopen(output_file_name,"wb");
    datos2 = malloc(sizeof(datos2) * maxgeneraciones * p * nodos);	if(datos2==0) printf("Error en malloc");
    fich2=fopen(output_file_fitness_name,"wb");

    cromo_sal1 = malloc(sizeof(cromo_sal1) * RESULTADOS * LONG_INDIV * nodos);	if(cromo_sal1==0) printf("Error en malloc");
    fitness1 = malloc(sizeof(fitness1) * RESULTADOS * nodos);	if(fitness1==0) printf("Error en malloc");
    cromo_sal2 = malloc(sizeof(cromo_sal2) * RESULTADOS * LONG_INDIV * nodos);	if(cromo_sal2==0) printf("Error en malloc");
    fitness2 = malloc(sizeof(fitness2) * RESULTADOS * nodos);	if(fitness2==0) printf("Error en malloc");
    cromo_sal2 = malloc(sizeof(cromo_sal2) * RESULTADOS * LONG_INDIV * nodos);	if(cromo_sal2==0) printf("Error en malloc");
    generacion = malloc(sizeof(generacion)* RESULTADOS * nodos);  if(generacion==0) printf("Error en malloc");
    tiempo = malloc(sizeof(tiempo)* RESULTADOS * nodos);  if(tiempo==0) printf("Error en malloc");
    cromo_entrada = malloc(sizeof(cromo_entrada)* LONG_INDIV * m);  if(cromo_entrada==0) printf("Error en malloc");
    orderesult = malloc(sizeof(orderesult) * nodos*RESULTADOS);	if(orderesult==0) printf("Error en malloc");
    aux_sal = malloc(sizeof(aux_sal) * nodos * maxgeneraciones * 2);	if(aux_sal==0) printf("Error en malloc");

    data_struct_ap1->objetivo = objetivo;
    data_struct_ap1->tamaobj = tamaobj;
    data_struct_ap1->pentarboles = pentarboles;
    data_struct_ap1->maxgen = maxgeneraciones;
    data_struct_ap1->cromo_sal = cromo_sal1;
    data_struct_ap1->fitness = fitness1;
    data_struct_ap1->cromo_entrada = cromo_entrada;
    data_struct_ap1->fitness_entrada = 0;
    data_struct_ap1->nivel_max = nivel_max;
    data_struct_ap1->vars= vars;
    data_struct_ap1->en_cromo_entrada = 0;
    data_struct_ap1->generacion = generacion;
    data_struct_ap1->tiempo = tiempo;
    data_struct_ap1->aux = aux;
    data_struct_ap1->aux_sal = aux_sal;

/*	printf("\npentarboles:%i nivel_max%i ", pentarboles ,nivel_max);*/
/*	fflush(stdout);	*/

        /* Iniciar evolucion */
        x = 0;
    for(k = 0; k < iteraciones ; k++)
    {
        tiempo1 = get_timestamp();
        iniciar_evol(data_struct_ap1);  //evolution
        tiempo2 = get_timestamp();
        *tiempo = tiempo2 - tiempo1;
        tiempof2 = *tiempo;
        tiempof = tiempof2/(1000000);
        printf("\n%i %i %i %5f",nodos, vars, poblacion_total, tiempof);
        //fprintf(fich, "\n%i %i %i %5f",nodos, vars, poblacion_total, tiempof);

        for(i = 0; i < nodos*RESULTADOS; i++)	//Organizar lo q llego, ¡solo se indexa orderesult, que dice en q orden estan los cromosomas!
        {
            *(orderesult + i) = i;	//se inicializa el stream para el orden
        }

        for(i=0; i< nodos*RESULTADOS; i++)
        {
            for(j=i+1; j< nodos*RESULTADOS; j++)
            {
                if(*(fitness1 + j) < *(fitness1 + i))
                {
                    aux1 = *(orderesult + i);
                    *(orderesult + i) = *(orderesult + j);
                    aux2 = *(fitness1 + i);
                    *(fitness1 + i) = *(fitness1 + j);
                    *(orderesult + j) = aux1;
                    *(fitness1 + j) = aux2;
                    aux1 = *(generacion + i);
                    *(generacion + i) = *(generacion + j);
                    *(generacion + j) = aux1;
                }
            }
        }

        for(i = 0; i < maxgeneraciones; i=i+maxgeneraciones)	//revisar mediciones
        {
            aux1 = 0;
            aux2 = 0;
            for(j = 0; j < nodos; j++)
            {
                aux1 = aux1 + *(aux_sal + (maxgeneraciones * 2 * j) + i);
                aux2 = aux2 + *(aux_sal + (maxgeneraciones * 2 * j) + maxgeneraciones + i);
            }
            aux1 = aux1 / nodos;
            aux2 = aux2 / nodos;
            if((x&(((iteraciones*p)/puntos)-1)) == 0x0)
                fprintf(fich2, "%i %i %i\n",(k*p)+i, aux1, aux2);

//            printf("%i %i %i %i\n",(k*p)+i, aux1, aux2, T);
        }

        for(i = 0; i < LONG_INDIV; i++ )
        {
           *(char *)(cromo_entrada + i) = *(char *)(cromo_sal1 + (*(orderesult)*LONG_INDIV) + i);
        }
        data_struct_ap1->en_cromo_entrada = 1;
        x = x + p;
        float1 = k;
        float2 = iteraciones;
        Tfloat = (float1/float2)*4;
        T = 1 + (int)Tfloat;
        aux = (T << 16) | p;
       	data_struct_ap1->aux = aux;
    }

    for(i=0; i < RESULTADOS-1 ;i++)
    {
        printf("\nfit%i:%i gnrcn:%i ", i, *(fitness1), *(generacion + *(orderesult + i)));
        mostrar_indiv(cromo_sal1 + ( *orderesult * LONG_INDIV ), pentarboles, vars);
    }

    x++;

	free(cromo_sal1);
	free(fitness1);
	free(cromo_sal2);
	free(fitness2);
	free(cromo_entrada);
	free(orderesult);
	free(generacion);
	free(tiempo);
	free(aux_sal);

fclose(fich);
fclose(fich2);

free(datos);
free(datos2);
free(funlut_ap);

return 0;
}
