/*********************************************************************************************************
** Programa para probar la sintesis combinacional mediante programacion genetica,
** se usan sockets para repartir carga de trabajo a otros clientes
** Se usa periferico evalfit del proyecto ehw3
** se aceleran 5 arboles, que en el presente codigo se llama pentarbol
** compilar con math.h   -lm
** compilar con threads: -lpthread
** powerpc-405-linux-gnu-gcc sintesishw_server.c -lm -lpthread -o sintesishw_server_ppc
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
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <sys/un.h>
#include <sintesishw_server.h>

/**************************************************************************************************************************************
	crea socket */
int crear_socket()
{
int fd;
struct sockaddr_in server;

   if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) /* Crear socket */
	{
      perror("socket");
      exit(-1);
   	}
   server.sin_family = AF_INET;
   server.sin_port = htons(PORT);    		/* cambiar endianismo */
   server.sin_addr.s_addr = INADDR_ANY;    	/* INADDR_ANY coloca nuestra direccion IP */
   bzero(&(server.sin_zero),8);    			/* escribimos ceros en el resto de la estructura */
	if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&server,sizeof(struct sockaddr)) == -1) /* permite reutilizar el puerto */
	{
	    perror("setsockopt");
	    exit(1);
	}
   if(bind(fd,(struct sockaddr*) & server, sizeof(struct sockaddr))==-1) //se asigna el socket
	{
		perror("bind");
	    exit(EXIT_FAILURE);
   }
return fd;
}


/*******************************************************************************************************************************/
/*******************************************************************************************************************************/
/*******************************************************************************************************************************/
/*******************************************************************************************************************************/

int main()
{
	int k, a, i, j = 0, error, vars = 4, *tiempo;
	int conta=0, aux1, aux2, pentarboles, *fitness1, *fitness2, *entrada, *generacion, aux, *aux_sal;
	char o, *ap, *valor_devuelto;;
	char *cromo_sal1, *cromo_sal2, *cromo_entrada, *cromo_ap_aux;
	int objetivo[8192];//= {0,254,123,16,87,56,34,76,89,155,199};
	struct gen_datos_tipo data_struct1, data_struct2;
	struct gen_datos_tipo *data_struct_ap1, *data_struct_ap2;

int nivel2[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int nivel3[]={0,0,1,1,1,2,2,2,2,3,3, 3, 3, 4, 4, 4};
int nivel4[]={0,0,0,0,0,1,1,1,1,1,1, 1, 1, 1, 1, 1};
int nivel5[]={0,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0};

/* Variables para tablas de lut*/
	FILE *f1, *f2;
	int size1, size2;

/* Variables para los sockets */
	int fd, fd2, numbytes; /* punteros para sockets */
	struct sockaddr_in server;
	struct sockaddr_in client;
	void *data_socket_rx_ap, *data_socket_tx_ap, *ap1;
	int sin_size;

/*para periferico*/
	int basemem;

	srand ( (time(NULL)) );

/* Tabla para las LUT*/
	f1 = fopen("funlut.dat","r");
	if(f1 == NULL){ printf("\nError de lectura de archivo!");return 0;}
	fseek (f1, 0, SEEK_END);
	size1 = ftell(f1);
	funlut_ap = malloc(size1);	if(funlut_ap==0) printf("Error en malloc");
	rewind (f1);
	fread(funlut_ap,1,size1,f1);
	fclose(f1);

	f2 = fopen("puertas.dat","r");
	if(f2 == NULL){ printf("\nError de lectura de archivo!");return 0;}
	fseek (f2, 0, SEEK_END);
	size2 = ftell(f2);
	puertas_ap = malloc(size2);	if(puertas_ap==0) printf("Error en malloc");
	rewind (f2);
	fread(puertas_ap,1,size2,f2);
	fclose(f2);

	basemem = open("/dev/mem", (O_RDWR | O_SYNC));  //abrir dispositivo memoria para mapear dir del periferico
	if(basemem == -1)
	{	printf("Error al abrir /dev/mem \n");
	return -1;}

/** iniciar periferico **/
	if(HW_ENABLE == 1){
		evalfit_ptr1 = (int *)init_peripheral(EVALFIT_PHYSBASE1, basemem);
/*
		evalfit_ptr2 = (int *)init_peripheral(EVALFIT_PHYSBASE2, basemem);
		evalfit_ptr3 = (int *)init_peripheral(EVALFIT_PHYSBASE3, basemem);
		evalfit_ptr4 = (int *)init_peripheral(EVALFIT_PHYSBASE4, basemem);
*/
	}
	data_struct_ap1 = &data_struct1;
	data_struct_ap2 = &data_struct2;

/* preparar socket para recibir */
	data_socket_rx_ap = malloc(100000);
	data_socket_tx_ap = malloc(100000);
	fd = crear_socket();
	if(listen(fd, BACKLOG) == -1)
	{ printf("error en listen()\n");
      exit(-1);
   	}

    //int err, sndsize=8192;
        //err = setsockopt(fd2, SOL_SOCKET, SO_RCVBUF, (char *)&sndsize, (int)sizeof(sndsize));

   while(1)
	{
      	sin_size=sizeof(struct sockaddr_in);
      	if ((fd2 = accept(fd,(struct sockaddr *)&client, &sin_size))==-1)       /* llamada a accept() */
		{
         printf("error en accept()\n");
         exit(-1);
      	}
/*		printf("Se obtuvo una conexion desde %s\n", inet_ntoa(client.sin_addr) );   //mostrara la IP del cliente QUITAR PARA GANAR VELOCIDAD*/

    numbytes=0;
    do
    {
		if ((aux1=recv(fd2,data_socket_rx_ap+numbytes,8192,0)) == -1){  /* recibir datos del cliente*/
      		perror("recv");
			printf("Error en recv() \n");
      		exit(-1);
   		}
   		numbytes = numbytes+aux1;
    }while(*(int *)(data_socket_rx_ap+numbytes-4)!=htonl(0xa55a9669));

		ap1 = data_socket_rx_ap;					/* Cargar datos en la estructura para la evolucion */
		data_struct_ap1->tamaobj = htonl(*(int *)ap1) & 0xFFFF;
		maxgeneraciones = htonl(*(int *)ap1) >> 16;
		//printf("\ntama obj:%0x maxgens:%i numbytes:%i-- ", data_struct_ap1->tamaobj, maxgeneraciones,numbytes);
		fflush(stdout);
		ap1 = ap1 + 4;
		for(i=0;i < (data_struct_ap1->tamaobj); i++)
		{
			objetivo[i] =htonl(*(int *)ap1);		//XX
			//printf("obj:%i %i ",i,objetivo[i]);
			ap1 = ap1 + 4;
		}
		data_struct_ap1->objetivo = objetivo;
		data_struct_ap1->pentarboles = htonl(*(int *)ap1) & 0XFF;
		pentarboles = data_struct_ap1->pentarboles;
		vars = htonl(*(int *)ap1) >> 16;
		data_struct_ap1->vars = vars;
		ap1 = ap1 + 4;
		data_struct_ap1->tamacrom = htonl(*(int *)ap1) & 0xFFFF;
		poblacion = htonl(*(int *)ap1) >> 16;
		//printf("\ntamacrom:%0x poblacion:%i vars:%i pentarboles:%i maxgeneraciones:%i ", data_struct_ap1->tamacrom, poblacion,vars,pentarboles,maxgeneraciones);
		ap1 = ap1 + 4;
		cromo_entrada = malloc(sizeof(cromo_entrada) * RESULTADOS * LONG_INDIV); if(cromo_entrada==0) printf("Error en malloc");
		data_struct_ap1->cromo_entrada = cromo_entrada;

		for(i = 0; i < (data_struct_ap1 -> tamacrom); i++)
		{
			*(char *)(cromo_entrada + i) = *(char *)ap1;
			ap1 = ap1 + 1;
		}

		data_struct_ap1->fitness_entrada = htonl(*(int *)ap1);
		ap1 = ap1 + 4;
		data_struct_ap1->nivel_max = htonl(*(int *)ap1) & 0xFFFF;
		data_struct_ap1->en_cromo_entrada = htonl(*(int *)ap1) >> 16;	//han enviado un cromosoma?
                ap1 = ap1 + 4;
                data_struct_ap1->aux = htonl(*(int *)ap1);
		//printf("\nnivel_max:%0x-- ", data_struct_ap1->nivel_max);
		data_struct_ap1->maxgen = maxgeneraciones;

		cromo_sal1 = malloc(sizeof(cromo_sal1) * RESULTADOS * LONG_INDIV); if(cromo_sal1==0) printf("Error en malloc"); /* reservar para cromosomas */
		fitness1 = malloc(sizeof(fitness1) * RESULTADOS);  if(fitness1==0) printf("Error en malloc");
		cromo_sal2 = malloc(sizeof(cromo_sal2) * RESULTADOS * LONG_INDIV); if(cromo_sal2==0) printf("Error en malloc");
		fitness2 = malloc(sizeof(fitness2) * RESULTADOS); if(fitness2==0) printf("Error en malloc");
		generacion = malloc(sizeof(generacion)); if(generacion==0) printf("Error en malloc");
		tiempo = malloc(sizeof(tiempo)* RESULTADOS );  if(tiempo==0) printf("Error en malloc");
		aux_sal = malloc(sizeof(aux_sal)* maxgeneraciones * 2 );  if(aux_sal==0) printf("Error en malloc");

		data_struct_ap1->generacion = generacion;
		data_struct_ap1->cromo_sal = cromo_sal1;
		data_struct_ap1->fitness = fitness1;
		data_struct_ap1->fitness_entrada = 0;
		data_struct_ap1->tiempo = tiempo;
		data_struct_ap1->aux_sal = aux_sal;

		*generacion = 0;

		evolucionar(data_struct_ap1);	// evolucionar

/*
		for(i=0; i < RESULTADOS ;i++)
		{
			printf(" %i-- fit:%i \t",i , *(fitness1 + i));
			mostrar_indiv(cromo_sal1 + (i*LONG_INDIV), pentarboles, vars);
		}
*/

		ap1 = data_socket_tx_ap;	/* devolver resultados */
		*(int *)ap1 = ntohl(LONG_INDIV);
		ap1 = ap1 + 4;

		for(i=0; i < RESULTADOS ;i++)
		{
		    for(j=0; j < LONG_INDIV ;j++)
			{
				*(char *)ap1 = *(cromo_sal1 + j + (LONG_INDIV * i));
				ap1 ++;
			}
			*(int *)ap1 = ntohl(((*generacion) << 16) | (*(fitness1 + i)));
			ap1 = ap1 + 4;
			*(int *)ap1 = ntohl(*tiempo);
			ap1 = ap1 + 4;
		}
		for(i=0; i < maxgeneraciones*2 ;i++)    //devolver mediciones
		{
            *(int *)ap1 = ntohl(*(aux_sal+i));
            ap1 = ap1 + 4;
		}
		numbytes = ap1 - data_socket_tx_ap;
      	send(fd2, data_socket_tx_ap, numbytes, 0);       /* devuelve cromosoma y fitness al cliente */
/*		printf("\n");*/

      	close(fd2);
		free(cromo_entrada);
		free(cromo_sal1);
		free(fitness1);
		free(cromo_sal2);
		free(fitness2);
		free(generacion);
		free(tiempo);
		free(aux_sal);
   	}


if(HW_ENABLE == 1){
	close_peripheral(evalfit_ptr1);
/*
	close_peripheral(evalfit_ptr2);
	close_peripheral(evalfit_ptr3);
	close_peripheral(evalfit_ptr4);
*/
}
close(basemem);


free(funlut_ap);
free(puertas_ap);
free(data_socket_rx_ap);
free(data_socket_tx_ap);
shutdown(fd, SHUT_RDWR);
close(fd);

return 0;
}
